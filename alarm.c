
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <time.h>

void handler(int sig)
{
    printf("alarm got\n");
}

int main()
{

    struct sigaction  sa;
    sa.sa_handler = handler; 

    struct timespec ts;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    alarm(2);
    sleep(6);
}
