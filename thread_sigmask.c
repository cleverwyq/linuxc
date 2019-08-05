#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

void * thread_task(void *args)
{
    int sig;
    sigset_t *set = (sigset_t*)args;
    
    //pthread_sigmask(SIG_SETMASK, set, NULL);
    //sleep(4);
    //printf("[Thread ]: wake up after 4 seconds\n");
    //pthread_sigmask(SIG_UNBLOCK, set, NULL);

    sigdelset(set, SIGINT);
    while(1) {
      printf("[Thread] : wait for signal \n");
      int s = sigwait(set, &sig); 
      printf("[Thread] : got signal %d\n", sig); 
    }
    
    printf("[Thread]: Finshed\n");
}

int main()
{
    sigset_t sigset;

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGUSR1);
    pthread_sigmask(SIG_SETMASK, &sigset, NULL);

    pthread_t id;
    pthread_create(&id, NULL, thread_task, (void*)&sigset);
    printf("main will sleep 10 seconds\n");
    sleep(10);
    printf("[Main]: wakeup after 10 seconds\n");

    int sig;
    printf("[Main]: wait for sigset\n");
    sigwait(&sigset, &sig);
    printf("[Main] : got signal %d\n", sig);
    sigwait(&sigset, &sig);
    printf("[Main] : got signal %d\n", sig);
    pause();
}