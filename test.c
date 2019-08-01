#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
 
#define NUM 5
int queue[NUM];
int current_num; 
 
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_cond_t blank_product = PTHREAD_COND_INITIALIZER;
 
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
 
void *producer(void *arg)
{
    int p = 0, i;
    while(1){
        
        pthread_mutex_lock(&lock);
        while(current_num >= NUM) {
            pthread_cond_wait(&blank_product, &lock);
        }
 
        queue[p] = rand() % 1000 + 1;
        printf("produce %d\n", queue[p]);
        p = (p + 1) % NUM;
        current_num ++;
        pthread_mutex_unlock(&lock);
        
        printf("after produce --- current_num: %d\n", current_num);
        for(i=0; i < NUM; i++) {
            printf("%d ", queue[i]);
        }
        putchar('\n');
 
        sleep(1);
       //sleep(rand()%5);
       
        pthread_cond_signal(&has_product);       
    }    
}
 
void *consumer(void *arg)
{
    int c = 0, i;
    while(1) {
       
        
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&has_product, &lock);
        printf("consume %d\n", queue[c]);
        
        queue[c] = 0;
        c = (c+1)%NUM;   
        current_num--;
        printf("after consume --- current_num: %d\n", current_num);
        for(i=0; i < NUM; i++) {
            printf("%d ", queue[i]);
        }
        putchar('\n');
    
        pthread_mutex_unlock(&lock);
       
        sleep(3);
        //sleep(rand()%5);
        
        pthread_cond_signal(&blank_product);
    }
}
 
int main()
{
    pthread_t pid, cid;
 
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
    printf("----\n");
    return 0;
}
