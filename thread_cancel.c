#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* task(void *args)
{  
    int oldtype;
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldtype);  
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &oldtype);
    printf("old type is %d\n", oldtype);
    
    int count = 0;
    while(1) {
        count++;
        printf("thread output %d\n", count);
        
        if ( count % 1024 == 0) {
            printf("test cancel at %-6d\n", count);
            //pthread_testcancel();
            manpthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldtype);
        }

    }
}

int main()
{
    pthread_t  id;
    pthread_create(&id, NULL, task, NULL);
    
  
    sleep(2);
    printf("notice calcel\n");
    pthread_cancel(id);   
    
 

    void *ret = 0;
    pthread_join(id, &ret);
    printf("exit status of thread is %d\n", ret);
  
    
}