#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int search(int frames[], int n, int key) {
  for (int i = 0; i < n; i++) 
    if (frames[i] == key)
      return 1;
  return 0;
}
int fifo(int pages[], int n, int frames_count) {
  int frames[10], faults = 0, index = 0;
  for (int i = 0; i < frames_count; i++)
    frames[i] = -1;
  for (int i = 0; i < n; i++) {
    if (!search(frames, frames_count, pages[i])){
      frames[index] = pages[i];
      index = (index + 1) % frames_count;
      faults++;
    }
  }
  return faults;
}
int lru(int pages[], int n, int frames_count) {
  int frames[10], time[10], faults = 0, counter = 0;
  for (int i = 0; i < frames_count; i++) 
    frames[i] = -1;
  for (int i = 0; i < n; i++) {
    int found = 0;
    for (int j = 0; j < frames_count; j++) {
      if (frames[j] == pages[i]) {
        counter++;
        time[j] = counter;
        found = 1;
        break;
      }
    }
    if (!found) {
      int min = 9999, pos = 0;
      for (int j = 0; j < frames_count; j++) {
        if (frames[j] == -1) {
          pos = j;
          break;
        }
        if (time [j] < min) {
          min = time[j];
          pos = j;
        }
      }
      frames[pos] = pages[i];
      counter++;
      time[pos] = counter;
      faults++;
    }
  }
  return faults;
}
int optimal(int pages[], int n, int frames_count) {
  int frames[10], faults = 0;
  for (int i = 0; i < frames_count; i++) 
    frames[i] = -1;
  for (int i = 0; i < n; i++) {
    if (!search(frames, frames_count, pages[i])) {
      int pos = -1, farthest = i;
      for (int j = 0; j < frames_count; j++) {
        int k;
        for (k = i + 1; k < n; k++)
          if (frames[j] == pages[k])
            break;
        if (k == n) {
          pos = j;
          break;
        }
        if (k > farthest) {
          farthest = k;
          pos = j;
        }
      }
      if (pos == -1)
        pos = 0;
      frames[pos] = pages[i];
      faults++;
    }
  }
  return faults;
}
int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("invalid number of arguments");
    return 1;
  }
  int n = atoi(argv[1]);
  int frames_count = atoi(argv[2]);
  int pages[100];
  srand(time(NULL));
  printf("reference string: \n");
  for (int i = 0; i < n; i++) {
    pages[i] = rand() % 10;
    printf("%d ", pages[i]);
  }
  printf("\n\n");
  int fifo_faults = fifo(pages, n, frames_count);
  int lru_faults = lru(pages, n, frames_count);
  int opt_faults = optimal(pages, n, frames_count);
  printf("FIFO: \n");
  printf("Page Faults = %d\n", fifo_faults);
  printf("Page Hits = %d\n", n - fifo_faults);
  printf("Hit Rate = %.2f\n", (float)(n - fifo_faults) / n);
  printf("Miss Rate = %.2f\n\n", (float)fifo_faults / n);
  printf("LRU:\n");
  printf("Page Faults = %d\n", lru_faults);
  printf("Page Hits = %d\n", n - lru_faults);
  printf("Hit Rate = %.2f\n", (float)(n - lru_faults) / n);
  printf("Miss Rate = %.2f\n\n", (float)lru_faults / n);
  printf("Optimal:\n");
  printf("Page Faults = %d\n", opt_faults);
  printf("Page Hits = %d\n", n - opt_faults);
  printf("Hit Rate = %.2f\n", (float)(n - opt_faults) / n);
  printf("Miss Rate = %.2f\n", (float)opt_faults / n);
  return 0;
}
