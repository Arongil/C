#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define MAX 1000000

void doubleToComplex(double complex destination[], const float arr[], int n) {
    for (int i = 0; i < n; i++) {
        destination[i] = arr[i] + 0*I;
    }
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

int check(int n)    //checking if the number of element is a power of 2
{
  return n > 0 && (n & (n - 1)) == 0;
}

int reverse(int N, int n)    //calculating revers number
{
  int j, p = 0;
  for(j = 1; j <= int_log2(N); j++) {
    if(n & (1 << (int_log2(N) - j)))
      p |= 1 << (j - 1);
  }
  return p;
}

void ordina(double complex* f1, int N) //using the reverse order in the array
{
  double complex f2[MAX];
  for(int i = 0; i < N; i++)
    f2[i] = f1[reverse(N, i)];
  for(int j = 0; j < N; j++)
    f1[j] = f2[j];
}

double complex from_polar(double mag, double angle) {
    return mag * cos(angle) + mag * sin(angle) * I;
}

void FFT(double complex* f, int N) //
{
  ordina(f, N);    //first: reverse order
  double complex *W;
  W = (double complex *)malloc(N / 2 * sizeof(double complex));
  W[0] = 1;
  W[1] = from_polar(1., -2. * M_PI / N);
  for(int i = 2; i < N / 2; i++)
    W[i] = W[i - 1] * W[1];
  int n = 1;
  int a = N / 2;
  for(int j = 0; j < int_log2(N); j++) {
    for(int i = 0; i < N; i++) {
      if(!(i & n)) {
        double complex temp = f[i];
        double complex Temp = W[(i * a) % (n * a)] * f[i + n];
        f[i] = temp + Temp;
        f[i + n] = temp - Temp;
      }
    }
    n *= 2;
    a = a / 2;
  }
  free(W);
}
