// A simple program that test how to use process,include fork(),etc
// 2015-12-14 07:22:49

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>


void test_fork_one();
void test_vfork();


int main()
{
    // get process
    printf("gid is %d\n",getpid());
    printf("my parent id is %d\n",getppid());

    //create process
    pid_t child;
    int status;

    printf("this will demostrate how to get child status\n");
    //create child process
    if((child=fork())==-1)
    {
        printf("fork error: %s \n",strerror(errno));
        exit(1);
    }
    else if(child == 0)     //child process
    {
        int i;
        printf("i am the child:%d\n",getpid());
        for(i=0;i<1000000;i++) sin(i);
        i = 5;
        printf("i exit with %d \n",i);
        exit(i);
    }


    printf("test vfork() function\n");
    test_vfork();

    printf("test :\n");
    test_fork_one();
    return 0;
}

void test_fork_one()
{
    int a =5;
    int b = 2;
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        a = a-4;
        printf("i'am a child process with PID(%d),the value of a:%d,the value of b:%d.\n",pid,a,b);
    }
    else if(pid < 0 )
    {
        perror("fork");
    }
    else
    {
        printf("i'm a parent process,with PID[%d],the value of a:%d,the value of b:%d.\n",pid,a,b);
    }
}



void test_vfork()
{
    if(vfork() == 0)
    {
        printf("this is the child process\n");
        exit(0);
    }
    else
    {
        printf("this is the parent process\n"); 
    }
}
