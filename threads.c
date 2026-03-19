#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
int arr[100];
int n;
double mean, median, stddev;
void *calc_mean(void *arg) {
  double sum = 0;
  for (int i = 0; i < n; i++)
    sum += arr[i];
  mean = sum / n;
  pthread_exit(NULL);
}
void *calc_median(void *arg) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (arr[i] > arr[j]) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
  if (n % 2 == 0) 
    median = (arr[n/2 -1] + arr[n/2 + 1]) / 2.0;
  else 
    median = arr[n/2];
  pthread_exit(NULL);
}
void *calc_stddev(void *arg) {
  int sum = 0;
  for (int i = 0; i < n; i++) 
    sum += (arr[i] - mean) * (arr[i] - mean);
  stddev = sqrt(sum / n);
  pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
  pthread_t t1, t2, t3;
  if (argc < 2) {
    printf("invalid number of arguments\n");
    return 1;
  }
  n = argc - 1;
  for (int i = 0; i < n; i++)
    arr[i] = atoi(argv[i + 1]);
  pthread_create(&t1, NULL, calc_mean, NULL);
  pthread_create(&t2, NULL, calc_median, NULL);
  pthread_join(t1, NULL);
  pthread_create(&t3, NULL, calc_stddev, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  printf("mean = %.2f\n", mean);
  printf("median = %.2f\n", median);
  printf("standard deviation = %.2f\n", stddev);
  return 0;
}
