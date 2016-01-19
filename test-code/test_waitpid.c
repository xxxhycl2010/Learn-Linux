// A simple program that test waitpid function
// 2015-12-14 20:29:13

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void die(const char *msg)
{
    perror(msg);
    exit(1);
}

void child2_do()
{
    printf("the child2: extcute 'date'\n");
    sleep(5);
    if(execlp("date","date",NULL) <0)
    {
        perror("child2 execlp");
    }
}

void child1_do(pid_t child2,char *argv)
{
    pid_t pw;
    do
    {
        if(*argv == '1')
        {
            pw = waitpid(child2,NULL,0);
        }
        else
        {
            pw = waitpid(child2,NULL,WNOHANG);
        }
        if(pw == 0)
        {
            printf("in child1 process:\n the child2 process has not exited!\n");
            sleep(1);
        }
    }while(pw ==0);
    if(pw == child2)
    {
        printf("get child2 %d.\n",pw);
        sleep(5);
        if(execlp("pwd","pwd",NULL) <0)
        {
            perror("child1 execlp");
        }
    }
    else
    {
        printf("error occured!\n");
    }
}

void father_do(pid_t child1,char *argv)
{
    pid_t pw;
    do
    {
        if(*argv == '1')
        {
            pw = waitpid(child1,NULL,0);
        }
        else
        {
            pw = waitpid(child1,NULL,WNOHANG);
        }
        if(pw == 0)
        {
            printf("in father process:\n the child1 process has not exited\n");
            sleep(1);
        }
    }while(pw == 0);

    if(pw == child1)
    {
        printf("get child1 %d\n",pw);
        sleep(5);
        if(execlp("ls","ls","-1",NULL) <0)
        {
            perror("father execlp");
        }
    }
    else
    {
        printf("error occured!\n");
    }
}

int main(int argc,char *argv[])
{
    pid_t child1,child2;
    if(argc <3)
    {
        printf("usage: waitpid [0 1][0 1]\n");
        exit(1);
    }

    child1 = fork();
    if(child1 < 0)
    {
        die("child1 fork");
    }
    else if(child1 == 0)
    {
        child2 = fork();
        if(child2 < 0)
        {
            die("child2 fork");
        }
        else if(child2 == 0)
        {
            child2_do();
        }
        else
        {
            child1_do(child2,argv[1]);
        }
    }
    else
    {
        father_do(child1,argv[2]);
    }

    return 0;
}
