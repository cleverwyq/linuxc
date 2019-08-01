#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_NUM 100
int counter = 0;
pthread_mutex_t  tmu = PTHREAD_MUTEX_INITIALIZER;
void* function(void *ptr)
{
    pthread_mutex_lock(&tmu);
    int c = counter;
    c++;
    usleep(1000);
    counter =  c;
    pthread_mutex_unlock(&tmu);
}

int main()
{
    pthread_t threads[THREAD_NUM];
    for(int i= 0; i < THREAD_NUM; i++) {
        pthread_create(&threads[i], NULL, function, NULL);
    }

    for(int j  = 0; j < THREAD_NUM; j++) {
        pthread_join(threads[j], NULL);
    }

    printf("counter =  %d\n", counter);
}