#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "portaudio.h"
#include "fftw3.h"

/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (1)
#define NUM_CHANNELS    (1)
/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) 

#define WRITE_TO_FILE   (0)

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

typedef struct
{
    int          frameIndex;  /* Index into sample array. */
    int          maxFrameIndex;
    SAMPLE      *recordedSamples;
}
paTestData;

/* This routine will be called by the PortAudio engine when audio is needed.
** It may be called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int recordCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    paTestData *data = (paTestData*)userData;
    const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
    SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
    long framesToCalc;
    long i;
    int finished;
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

    (void) outputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    if( framesLeft < framesPerBuffer )
    {
        framesToCalc = framesLeft;
        finished = paComplete;
    }
    else
    {
        framesToCalc = framesPerBuffer;
        finished = paContinue;
    }

    if( inputBuffer == NULL )
    {
        for( i=0; i<framesToCalc; i++ )
        {
            *wptr++ = SAMPLE_SILENCE;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = SAMPLE_SILENCE;  /* right */
        }
    }
    else
    {
        for( i=0; i<framesToCalc; i++ )
        {
            *wptr++ = *rptr++;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
        }
    }
    data->frameIndex += framesToCalc;
    return finished;
}

/* This routine will be called by the PortAudio engine when audio is needed.
** It may be called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
//static int playCallback( const void *inputBuffer, void *outputBuffer,
//                         unsigned long framesPerBuffer,
//                         const PaStreamCallbackTimeInfo* timeInfo,
//                         PaStreamCallbackFlags statusFlags,
//                         void *userData )
//{
//    paTestData *data = (paTestData*)userData;
//    SAMPLE *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
//    SAMPLE *wptr = (SAMPLE*)outputBuffer;
//    unsigned int i;
//    int finished;
//    unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;
//
//    (void) inputBuffer; /* Prevent unused variable warnings. */
//    (void) timeInfo;
//    (void) statusFlags;
//    (void) userData;
//
//    if( framesLeft < framesPerBuffer )
//    {
//        /* final buffer... */
//        for( i=0; i<framesLeft; i++ )
//        {
//            *wptr++ = *rptr++;  /* left */
//            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
//        }
//        for( ; i<framesPerBuffer; i++ )
//        {
//            *wptr++ = 0;  /* left */
//            if( NUM_CHANNELS == 2 ) *wptr++ = 0;  /* right */
//        }
//        data->frameIndex += framesLeft;
//        finished = paComplete;
//    }
//    else
//    {
//        for( i=0; i<framesPerBuffer; i++ )
//        {
//            *wptr++ = *rptr++;  /* left */
//            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
//        }
//        data->frameIndex += framesPerBuffer;
//        finished = paContinue;
//    }
//    return finished;
//}


/*******************************************************************/
int listen(paTestData *data) {
    PaStreamParameters  inputParameters,
                        outputParameters;
    PaStream*           stream;
    PaError             err = paNoError;
    int                 numSamples;
    int                 numBytes;

    printf("The genie is listening...\n"); fflush(stdout);

    numSamples = data->maxFrameIndex * NUM_CHANNELS;
    numBytes = numSamples * sizeof(SAMPLE);

    err = Pa_Initialize();
    if( err != paNoError ) goto done;

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (inputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default input device.\n");
        goto done;
    }
    inputParameters.channelCount = NUM_CHANNELS;                    /* stereo input */
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    /* Record some audio. -------------------------------------------- */
    err = Pa_OpenStream(
              &stream,
              &inputParameters,
              NULL,                  /* &outputParameters, */
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              recordCallback,
              data );
    if( err != paNoError ) goto done;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto done;
    printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);

    while( ( err = Pa_IsStreamActive( stream ) ) == 1 )
    {
        Pa_Sleep(1000);
        // printf("index = %d\n", data->frameIndex ); fflush(stdout);
    }
    if( err < 0 ) goto done;

    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto done;

    /* Playback recorded data.  -------------------------------------------- */
    data->frameIndex = 0;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
        goto done;
    }
    outputParameters.channelCount = NUM_CHANNELS;                     /* stereo output */
    outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

//    printf("\n=== Now playing back. ===\n"); fflush(stdout);
//    err = Pa_OpenStream(
//              &stream,
//              NULL, /* no input */
//              &outputParameters,
//              SAMPLE_RATE,
//              FRAMES_PER_BUFFER,
//              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
//              playCallback,
//              data );
//    if( err != paNoError ) goto done;
//
//    if( stream )
//    {
//        err = Pa_StartStream( stream );
//        if( err != paNoError ) goto done;
//        
//        printf("Waiting for playback to finish.\n"); fflush(stdout);
//
//        while( ( err = Pa_IsStreamActive( stream ) ) == 1 ) Pa_Sleep(100);
//        if( err < 0 ) goto done;
//        
//        err = Pa_CloseStream( stream );
//        if( err != paNoError ) goto done;
//        
//        printf("Done.\n"); fflush(stdout);
//    }

done:
    Pa_Terminate();
    // if( data->recordedSamples )       /* Sure it is NULL or valid. */
    //    free( data->recordedSamples );
    if( err != paNoError )
    {
        fprintf( stderr, "An error occured while using the portaudio stream\n" );
        fprintf( stderr, "Error number: %d\n", err );
        fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
        err = 1;          /* Always return 0 or 1, but no other return codes. */
    }
    return err;
}

/*******************************************************************/
double *toDouble(float *arr, int n) {
    double *converted = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        converted[i] = (double)arr[i];
    }
    return converted;
}

int int_log2(int N)    /*function to calculate the log2(.) of int numbers*/
{
  int k = N, i = 0;
  while(k) {
    k >>= 1;
    i++;
  }
  return i - 1;
}

double *pad_to_power_of_2(double *arr, int n, int *new_len) {
    int l2 = int_log2(n);
    *new_len = pow(2, l2 + 1);
    double *padded = malloc(*new_len * sizeof(double));
    for (int i = 0; i < n; i++) {
        padded[i] = arr[i];
    }
    for (int i = n; i < *new_len; i++) {
        padded[i] = 0;
    }
    return padded;
}

void fft(double *data, double *real_out, int N) {
    fftw_complex *in, *out;
    fftw_plan my_plan;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);

    for (int i = 0; i < N; i++) {
        in[i] = data[i] + 0*I;
    }
    my_plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(my_plan);
    fftw_destroy_plan(my_plan);
    fftw_free(in);

    for (int i = 0; i < N; i++) {
        real_out[i] = cabs(out[i]);
    }
    fftw_free(out);
}
/*******************************************************************/
void normalize(double *dest, const double *src, int n) {
    double mag = 0;
    for (int i = 0; i < n; i++) {
        mag += src[i]*src[i];
    }
    double inv_mag = 1 / sqrt(mag);
    for (int i = 0; i < n; i++) {
        dest[i] = src[i] * inv_mag;
    }
}

double normalized_diff(double *freq1, double *freq2, int n) {
    double *normalized1 = malloc(n * sizeof(double));
    double *normalized2 = malloc(n * sizeof(double));
    normalize(normalized1, freq1, n);
    normalize(normalized2, freq2, n);
    double sum = 0, d;
    for (int i = 0; i < n; i++) {
        d = normalized1[i] - normalized2[i];
        sum += d*d;
    }
    free(normalized1);
    free(normalized2);
    return sum;
}

int read_key(double *arr, int n) {
    FILE *genie_key = fopen("genie_key.txt", "r");
    for (int i = 0; i < n; i++) {
        if (fscanf(genie_key, "%lf", &arr[i]) != 1) {
            return 1;
        }
    }
    return 0;
}

int genie_accept(double *freq, int n) {
    double threshold = 0.8;
    double *key = malloc(n * sizeof(double));
    if (read_key(key, n) == 1) {
        printf("Error: mismatch between the size of the audio sample and the key.");
    }
    double d = normalized_diff(freq, key, n);
    if (d > threshold) {
        printf("\nYou score %.3lf > %.3lf.", d, threshold);
    } else {
        printf("\nYou score %.3lf < %.3lf.", d, threshold);
    }
    free(key);
    return d < threshold;
}
/*******************************************************************/
int init_data(paTestData *data) {
    int numSamples;
    int numBytes;
    int i;

    data->maxFrameIndex = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
    data->frameIndex = 0;
    numSamples = data->maxFrameIndex * NUM_CHANNELS;
    numBytes = numSamples * sizeof(SAMPLE);
    data->recordedSamples = (SAMPLE *) malloc( numBytes ); /* From now on, recordedSamples is initialised. */
    if( data->recordedSamples == NULL )
    {
        printf("Could not allocate record array.\n");
        return 1;
    }
    for( i=0; i<numSamples; i++ ) data->recordedSamples[i] = 0;
    
    return 0;
}
/*******************************************************************/
int attempt_genie() {
    paTestData data;

    init_data(&data);
    listen(&data);

    int n = data.maxFrameIndex * NUM_CHANNELS;
    int next_pow_of_2 = n;
    double *samples = toDouble(data.recordedSamples, n);
    double *padded_samples = pad_to_power_of_2(samples, n, &next_pow_of_2);
    double *out = malloc(next_pow_of_2 * sizeof(double));
    fft(padded_samples, out, next_pow_of_2);

    int status = genie_accept(out, next_pow_of_2); 

    free(data.recordedSamples);
    free(samples);
    free(padded_samples);
    free(out);

    return status;
}

void reset_key() {
    paTestData data;

    init_data(&data);
    listen(&data);

    int n = data.maxFrameIndex * NUM_CHANNELS;
    int next_pow_of_2 = n;
    double *samples = toDouble(data.recordedSamples, n);
    double *padded_samples = pad_to_power_of_2(samples, n, &next_pow_of_2);
    double *out = malloc(next_pow_of_2 * sizeof(double));
    fft(padded_samples, out, next_pow_of_2);

    FILE *genie_key = fopen("genie_key.txt", "w");
    for (int i = 0; i < next_pow_of_2; i++) {
        fprintf(genie_key, "%.3f\n", out[i]);
    }

    free(data.recordedSamples);
    free(samples);
    free(padded_samples);
    free(out);
}
