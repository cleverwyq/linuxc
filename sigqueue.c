#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char buf[128];
union sigval sv;
void handler(int sig,  siginfo_t* si,  void *arg)
{
    //printf("[%d] Got info from child :\n", getpid());
    //printf("...%x\n", (char*)(si->si_ptr));
    //printf("in fact , buf is %s\n", buf);
    printf("got %s from child\n", (char*)(si->si_ptr));
    //printf("finish sig handler\n");
}


int main()
{

    int pid = fork();
    strcpy(buf, "hello world");
    if (pid == 0)  //child process
    {   
        //char *buf = malloc(128);
        sv.sival_ptr = buf;
        
        sleep(3);
        //printf("child : buf value : %s, address:%x\n", buf, buf);
        printf("Parent : %d send to %d\n", getpid(), pid);
        int q = sigqueue(getppid(), SIGUSR1, sv);
        printf("result of sig %d\n", q);
    }
    else if (pid > 0)
    {   
        struct sigaction sa;
        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = handler;
        sigemptyset(&sa.sa_mask);

        sigaction(SIGUSR1, &sa, 0);
        //sleep(10);
        printf("wait for signal\n");
        pause();
        printf("Parent wake up and exit\n");
    }
}