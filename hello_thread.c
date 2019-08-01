#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* print_message(void *ptr)
{
    char* message = (char*)ptr;
    printf("Got message : %s\n", message);
    pthread_exit((void*)33);
}

int main()
{
    pthread_t thread1, thread2;
    char *m1 = "Thread1 says";
    char *m2 = "Thread2 says";
    int ret1, ret2;
    void *thread_return;

    ret1 = pthread_create(&thread1, NULL, print_message, (void*)m1);
    printf("return by create1 %d\n", ret1);

    ret2 = pthread_create(&thread2, NULL, print_message, (void*)m2);
    printf("thread id :%ld, return by create1 %d\n", thread2, ret2);

    pthread_join(thread1, NULL);

    
    pthread_join(thread2, &thread_return);
    printf("return value from thread1 : %d\n", (int)(int*)(thread_return));
    printf("88 from main\n");

}