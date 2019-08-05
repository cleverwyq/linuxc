#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int timeread = 0;
int seconds_now = -1, seconds_last = -1;
void display_sigset(sigset_t sigset)
{
    printf("\n--------->\n");
    for(int i = 1; i < _NSIG; i++)
    {
        if (sigismember(&sigset, i))
            psignal(i, "in pending:");
    }
    printf("\n<--------->\n");
}

void printf2(const char* info)
{   
    struct timeval tv;
    gettimeofday(&tv, 0);
    //printf("--- %ld ----\n", tv.tv_sec);

    seconds_now = tv.tv_sec;

    int diff = 0;
    if (seconds_last == -1 )
    {
        diff = 0;
        seconds_last = seconds_now;
    }
    else
    {
        diff = seconds_now - seconds_last;
    }
    

    printf("%3d  : %s =>", diff, info);
}