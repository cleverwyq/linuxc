#include <stdio.h>
#include <pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void  run_once()
{
    printf("function once run run\n");
    printf("run by %lu\n", pthread_self());
}

void* task1()
{
    printf("thread %lu enter\n", pthread_self());
    int ret = pthread_once(&once, run_once);
    printf("In thread %lu, ret is %d\n", pthread_self(), ret);
    printf("thread %lu exit\n", pthread_self());
}


int main()
{
    pthread_t  ids[5];
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&ids[i], NULL, task1, NULL);
    }
    for(int i = 0; i < 5; i++)
    {
        pthread_join(ids[i], NULL);
    }

    printf("exit main\n");
}