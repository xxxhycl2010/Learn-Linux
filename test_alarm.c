// A simple program that test alarm function
// 2015-12-15 07:08:51

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void handler()
{
    printf("hello\n");
}

int main()
{
    int i;
    signal(SIGALRM,handler);
    alarm(5);
    for(i=1;i<7;i++)
    {
        printf("sleep %d...\n",i);
        sleep(1);
    }
}
