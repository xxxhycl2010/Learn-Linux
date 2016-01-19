// A simple program that test sigaction function
// 2015-12-15 07:21:20
//

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void* show_handler(struct sigaction *act)
{
    switch(act->sa_flags)
    {
        case SIG_DFL:printf("default action.\n");break;
        case SIG_IGN:printf("ignore the signal.\n");break;
        default:printf("0x%x\n",*(int*)act->sa_handler);
    }
}

int main()
{
    // there are some bug that need to modify
    int i;
    struct sigaction act,oldact;
    act.sa_handler = show_handler;
    act.sa_flags = SA_ONESHOT|SA_NOMASK;
    sigaction(SIGUSR1,&act,&oldact);
    for(i = 5;i<15;i++)
    {
        printf("sa_handler of signal %2d = \n",i);
        sigaction(i,NULL,&oldact);
    }
}
