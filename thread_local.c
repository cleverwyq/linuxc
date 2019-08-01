#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_key_t key;
pthread_t  id1, id2;


void *task2(void *args)
{
     printf("thread no2 %lu is running\n", pthread_self());

    int value = 200;
    pthread_setspecific(key, (void*)value);
    
    printf("value in task 2 is %d\n", (int)pthread_getspecific(key));   
}

void* task1(void *args)
{
    printf("thread no1 %lu is running\n", pthread_self());

    int value = 100;
    pthread_setspecific(key, (void*)value);    
    
    pthread_create(&id2, NULL, task2, NULL);
    printf("thread 1 sleep\n");
    sleep(5);
    printf("thread 1 wake up!\n");

    
    printf("value in task 1 is %d\n", (int)pthread_getspecific(key));
}

int main()
{
    pthread_key_create(&key, NULL);

    int value = 50;
    pthread_setspecific(key, (void*)value);
    pthread_create(&id1, NULL, task1, NULL);
    printf("id of thread 1 : %lu\n", id1);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    printf("main thread %lu with value %d\n", pthread_self(), (int)pthread_getspecific(key));

    pthread_key_delete(key);
}