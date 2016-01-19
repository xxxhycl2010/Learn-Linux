// A simple program that test wait function
// 2015-12-14 20:23:40

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main()
{
    pid_t pid;
    int status,i;
    if(fork() == 0)
    {
        printf("this is the child process:pid = %d\n",getpid());
        exit(5);
    }
    else
    {
        sleep(1);
        printf("this is the parent process ,wait for child...\n");
        pid = wait(&status);
        i = WEXITSTATUS(status);
        printf("child's pid = %d exit status = %d\n",pid,i);
    }
    return 0;
}
