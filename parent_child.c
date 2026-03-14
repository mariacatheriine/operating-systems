#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
sem_t s;
void *child(void *arg) {
    printf("Child. \n");
    sem_post(&s);
    return NULL;
}
int main() {
    sem_init(&s, 0, 0);
    printf("Parent: begin\n");
    pthread_t t;
    pthread_create(&t, NULL, child, NULL);
    sem_wait(&s);
    printf("Parent: end\n");
    return 0;
}