// A simple program that test zombie process
// 2015-12-14 20:16:19

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    while(1)
    {
        pid_t chi = fork();
        if(chi == 0)
        {
            execl("/bin/bash","bash","-c","ls",NULL);

        }
        sleep(2);
    }
}


void TestZombie2()
{
    if(!fork())
    {
        printf("child pid = %d\n",getpid());
        exit(0);
    }
    //wait();
    //waitpid(-1,NULL,0);

    sleep(60);
    printf("parent pid = %d\n",getpid());
    exit(0);
}
