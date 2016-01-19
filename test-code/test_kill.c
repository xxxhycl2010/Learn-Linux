// A simple program that test kill function
// 2015-12-15 07:02:50

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
    pid_t pid;
    int status;
    if(!(pid = fork()))
    {
        printf("hi i am child process.\n");
        sleep(10);
        return;
    }
    else
    {
        printf("send signal to child process (%d)\n",pid);
        sleep(1);
        kill(pid,SIGABRT);
        wait(&status);
        if(WIFSIGNALED(status))
            printf("child process receive signal %d\n",WTERMSIG(status));
    }


    return 0;
}
