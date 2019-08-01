#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void ouch(int sig)
{
    if (sig == SIGINT)
        printf("ooo..., %d got\n", sig);
    else
    {
        printf("another one %d\n", sig);
    }
    
    //signal(SIGINT, SIG_DFL);
}

int main()
{
    //signal(SIGINT, ouch);
    struct sigaction act;
    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESETHAND;
    sigaction(SIGINT, &act, 0);
    sigaction(SIGPIPE, &act, 0);
    while(1) {
        printf("Hello world\n");
        sleep(1);
    }
}