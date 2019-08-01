#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void handler(int signum)
{
    if (signum ==  SIGINT)
        printf("handle sigint\n");
    else
    {
        printf("handler of others\n");
    }
    
}

int main()
{
    sigset_t sigset;
    sigset_t ign;
    struct sigaction sa;
    
    sigemptyset(&sigset);
    sigemptyset(&ign);

    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, 0);
    //igaction(SIGUSR1, &sa, 0);
    printf("Wait for the SIGINT signal\n");
    pause();

    sigaddset(&sigset, SIGINT);
    sigprocmask(SIG_SETMASK, &sigset, 0);
    printf("Please ctrl+c in 10 seconds\n");
    sleep(10);
    printf("10 seconds passed\n");

    sigpending(&ign);
    if (sigismember(&ign, SIGINT))
    {
        printf("You see that INT is ignored...\n");
    }

    printf("then try to del INT from mask\n");
    sigdelset(&sigset, SIGINT);
    int ret = sigsuspend(&sigset);
    if (ret == -1 && errno == EINTR)
        printf("error no is :%d\n", errno);


    printf("System will exits in 5 seconds\n");
    sleep(5);

}