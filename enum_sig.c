#include <signal.h>
#include <stdio.h>


int main()
{
    for(int i = 1; i < _NSIG; i++) {
        char buf[512];
        psignal(i, buf);
        printf("%s\n", buf);
    }

}