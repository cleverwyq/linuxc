#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t count_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int counter = 0;
int halt1 =  4, halt2 = 7;

// 4-8
void* func1(void *ptr)
{
    while(1)
    {    

        pthread_mutex_lock(&count_mtx);
        printf("func1 waiting....\n");
        pthread_cond_wait(&cond, &count_mtx);
        printf("func1 finish wait and to exec\n");
        counter ++;
        printf("In func1, --> %d\n", counter);

        pthread_mutex_unlock(&count_mtx);

        if (counter >= 10) {
            printf("also cagu you\n");
            return NULL;
        }

    }
}

//1-3 or 8-10
void* func2(void * ptr)
{
    for(; ;)
    {
        pthread_mutex_lock(&count_mtx);
        if (counter <= halt1 || counter >= halt2)
        {
            printf("func2 allows you do once\n");
            pthread_cond_signal(&cond);
            
        }
        else
        {
            counter++;
            printf("In func2, --> %d\n", counter);
        }
        
        pthread_mutex_unlock(&count_mtx);
        if (counter >= 10) 
        {
            //pthread_cond_signal(&cond);
            printf("caugh you\n");
            pthread_exit(0);
        }
                
    }

}

int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, &func1, NULL);
    pthread_create(&t2, NULL, &func2, NULL);
    pthread_join(t2, NULL);
    pthread_join(t1, NULL);

    printf("bye\n");
}