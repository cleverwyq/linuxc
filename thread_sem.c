#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define NUM 5
sem_t blank_sem, product_sem;
int queue[NUM];

pthread_cond_t product_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int current_number = 0;

void* consumer(void *args)
{
    int i = 0;
    while(1) {
        
        sem_wait(&product_sem);
        int j = 0;
        printf("queue : ");
        for ( ; j < NUM; j++) {
            printf(" %5d\t",queue[j]);
        }
        printf("\n");
        printf("consume %d\n", queue[i]);
        queue[i] = 0;
        i = (i + 1) % NUM;   
        sem_post(&blank_sem);

        sleep(3);
    }
} 

void *producer(void *args)
{
    int i = 0;
    while(1) {
        sem_wait(&blank_sem);
        int p = rand()%1000 + 1;
        int j = 0;
        printf("queue : ");
        for ( ; j < NUM; j++) {
            printf(" %5d\t",queue[j]);
        }
        printf("\n");
        printf("produce %d\n",p );
        queue[i++] = p;
        i = i % NUM;
        sem_post(&product_sem);

        sleep(1);
    }
}

void *cond_consumer(void *args)
{
    int i = 0;
    while (1) {
        pthread_mutex_lock(&mutex);
        while(current_number == 0) {
            printf("consumer : wait for product_cond\n");
            pthread_cond_wait(&product_cond, &mutex);
            printf("consumer : product_cond recved\n");
        }
        printf("before consume, queue : ");
        for(int j = 0; j < NUM; j++) {
            printf("%5d", queue[j]);
        }
        printf("\nconsume %d\n", queue[i]);
        queue[i] = 0;
        i = (i + 1) % NUM;
        current_number--;
        pthread_cond_signal(&blank_cond);
        pthread_mutex_unlock(&mutex);

        
        printf("signal blank, current_number = %d\n", current_number);
        sleep(1);
    }
}

void* cond_producer(void *args)
{
    int i = 0;
    while (1) {
        pthread_mutex_lock(&mutex);
        while (current_number >= NUM) {
            printf(">=\n");
            printf("producer :send signal\n");
            //pthread_cond_signal(&product_cond);
            pthread_cond_wait(&blank_cond, &mutex);
            printf("producer :blank recved\n");
        }

        printf("before produce, queue : ");
        for(int j = 0; j < NUM; j++) {
            printf("%5d", queue[j]);
        }
        int p = rand()%1000 + 1;
        printf("\nproduce : %d\n", p);
        queue[i] =p;
        i = (i + 1)%NUM;
        current_number++; pthread_cond_signal(&product_cond);
        pthread_mutex_unlock(&mutex);

       
        printf("sginal product, current_number = %d\n", current_number);
        sleep(1);
    }
}

int main()
{
    pthread_t cid, pid;
    memset(queue, 0, sizeof(int) * NUM);
    /* 
    sem_init(&blank_sem, 0, NUM);
    sem_init(&product_sem, 0, 0);
    */

    pthread_create(&pid, NULL, cond_producer, NULL);
    pthread_create(&cid, NULL, cond_consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
}