#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <curl/curl.h>
#include "cJSON.h"

int progress_callback(void *ptr, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    /*
    fprintf(stderr, "\r");
    fflush(stderr);
    fprintf(stderr, "Bytes Downloaded %li", dlnow);
    */
    
    return 0;
}

// file helper functions helpfully provided by Parth
size_t fileSize(FILE *f){
    fseek(f, 0L, SEEK_END);
    size_t pos = ftell(f);
    rewind(f);
    return pos;
}

size_t numLines(FILE *f){
    rewind(f);
    size_t fs = fileSize(f);
    size_t i = 0;
    while(ftell(f) < fs){
        char* current = malloc(fs);
        fgets(current,fs,f);
        free(current);
        i++;
    }
    rewind(f);
    return i;
}

void stringify(char* string, FILE *f){
    size_t fs = fileSize(f);
    size_t lines = numLines(f);
    for(int i = 0; i < lines; i++){
        char* line = malloc(fs);
        fgets(line,fs,f);
        string = strcat(string,line);
        free(line);
    }
}

// my code again :)
char *download_url(const char *url) {
    const char *data_store_name = "download_data_store";
    FILE *writer = fopen(data_store_name, "w+");

    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0); 
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback); 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, writer);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "ERROR: curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        fprintf(stderr, "\n");
        char *output = malloc(fileSize(writer));
        stringify(output, writer);

        fclose(writer);
        remove(data_store_name);
        curl_easy_cleanup(curl);

        return output;
    }
    
    return NULL;
}

int from_kelvin(double t) {
    return (int)round((t - 273.15) * 9/5 + 32);
}

int parse(const char * const json) {
    const cJSON *weather = NULL;
    const cJSON *w = NULL;
    const cJSON *main = NULL;
    const cJSON *sys = NULL;

    double temp, high, low;
    char *desc;
    int sunset;

    cJSON *weather_json = cJSON_Parse(json);
    if (weather_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }

    weather = cJSON_GetObjectItemCaseSensitive(weather_json, "weather");
    cJSON_ArrayForEach(w, weather)
    {
        cJSON *description = cJSON_GetObjectItemCaseSensitive(w, "description");
        desc = description->valuestring;
    }
    
    main = cJSON_GetObjectItemCaseSensitive(weather_json, "main");
    temp = cJSON_GetObjectItemCaseSensitive(main, "temp")->valuedouble;
    high = cJSON_GetObjectItemCaseSensitive(main, "temp_max")->valuedouble;
    low = cJSON_GetObjectItemCaseSensitive(main, "temp_min")->valuedouble;

    sys = cJSON_GetObjectItemCaseSensitive(weather_json, "sys");
    sunset = cJSON_GetObjectItemCaseSensitive(sys, "sunset")->valueint;

    int temp_fahrenheit = from_kelvin(temp);
    int high_fahrenheit = from_kelvin(high);
    int low_fahrenheit = from_kelvin(low);

    time_t sunset_time = (time_t) sunset;
    struct tm * timeinfo = localtime(&sunset_time);
    int hour = timeinfo->tm_hour;
    int minute = timeinfo->tm_min;
    char *am_pm;
    if (hour > 12) {
        am_pm = "PM";
    } else {
        am_pm = "AM";
    }
    hour = (hour - 1) % 12 + 1;

    printf("~-~-~-~-~-~\n\nIt's %i degrees outside with %s.\n\nThe high is %i and the low is %i.\n\nSunset is at %i:%i %s.\n\n~-~-~-~-~-~\n\n", temp_fahrenheit, desc, high_fahrenheit, low_fahrenheit, hour, minute, am_pm);

end:
    cJSON_Delete(weather_json);
    return 0;
}

void output_weather(const char *zipcode) {
    char *url = calloc(200, sizeof(char));
    sprintf(url, "http://api.openweathermap.org/data/2.5/weather?zip=%s&APPID=711f6a12520d4900ad4da340153c9877", zipcode);
    
    const char *download = download_url(url);
    parse(download);
}
