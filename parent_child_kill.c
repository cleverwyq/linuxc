#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t  inttrupted = 0;
void  handler(int sig)
{
    printf("got sigusr1\n");
    inttrupted = 1;
    printf("value to %d\n", inttrupted);
}

void child_function()
{
    printf("I am child with id %d\n", getpid());
    sleep(4);
    kill(getppid(), SIGUSR1);
}
int main()
{
    pid_t child_pid;
    signal(SIGUSR1, handler);
    child_pid = fork();
    if (child_pid == 0)
        child_function();
    else 
    while(!inttrupted) {
        printf("wait for child\n");
        sleep(1);
    }

    printf("main process exit now\n");
}