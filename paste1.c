#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "common.h"

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

void handler(int sig);

int main(int argc, char *argv[])
{
    printf("new format\n");
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = 0;

    if (sigaction(SIGINT, &act, NULL) < 0)
        ERR_EXIT("sigaction error");

    struct sigaction act2;
    act2.sa_handler = handler;
    sigemptyset(&act2.sa_mask);
    act2.sa_flags = 0;

    if (sigaction(SIGQUIT, &act2, NULL) < 0)
        ERR_EXIT("sigaction error");

    sigset_t pend;
    sigpending(&pend);
    display_sigset(pend);
    
    struct sigaction act3;
    act3.sa_handler = handler;
    sigemptyset(&act3.sa_mask);
    act3.sa_flags = 0;

    if (sigaction(SIGUSR2, &act3,  NULL) < 0)
        ERR_EXIT("sigaction error");


    for (;;)
        pause();
    return 0;
}

void handler(int sig)
{
    sigset_t pending;
    sigpending(&pending);
    //display_sigset(pending);

    if(sig == SIGINT){

        printf2("recv a SIGINT signal\n");
        sleep(5);
        printf2("INT hanlder wakeup after 5 seconds!\n");
    }
    if (sig == SIGQUIT)
    {
        printf2("recv a SIGQUIT signal\n");
        sleep(30);
        printf2("quit handler wakeup after 30 seconds\n");
    }
    if (sig == SIGUSR2)
    {
        printf2("recv a SIGUSR2\n");
        sleep(15);
        printf2("SIGUSR2 up after 15 seconds\n");
    }
}