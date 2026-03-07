#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#define MAX 10
int buffer[MAX];
int fill = 0;
int use = 0;
int loops = 10;
sem_t full;
sem_t empty;
sem_t mutex;
void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
}
int get() {
    int temp = buffer[use];
    use = (use + 1) % MAX;
    return temp;
}
void *producer(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);
        put(i);
        sem_post(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *arg) {
    int i, temp = 0;
    for (i = 0; i < loops; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        temp = get();
        sem_post(&mutex);
        sem_post(&empty);
        printf("%d \n", temp);
    }
}
int main() {
    pthread_t p, c;
    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1); 
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    return 0;
}