#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_key_t key;
pthread_once_t once = PTHREAD_ONCE_INIT;


void create_key()
{
    pthread_key_create(&key, NULL);
}

void* accumulate(void *args)
{
    pthread_once(&once, create_key);
    char *accu = (char*)pthread_getspecific(key);
    if (accu == NULL)
    {
        accu = malloc(256);
        memset(accu, 1024, 0);
        pthread_setspecific(key, (void*)accu);
        printf("thread %lx allocate buffer @ %lu\n", pthread_self(), accu);
    }

    strcat(accu, (char*)args);

    return accu;
}

void* process(void *args)
{
    char *res = NULL;
    res = accumulate("Result of ");
    if (strcmp((char*)args, "first"))
        sleep(3);
    
    res = accumulate("thread ");
    res = accumulate((char*)args);

    printf("result of %lx --> %s\n", pthread_self(), res);

    return NULL;
}

int main()
{
    pthread_t id1, id2;
    char *res = accumulate("main result ");
    pthread_create(&id1, NULL, process, "first ");
    pthread_create(&id2, NULL, process, "second ");

    
    res = accumulate("Init thread");
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    printf("here is main %s\n", res);
}