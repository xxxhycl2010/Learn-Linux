// A simple program that test signal function
// 2015-12-15 07:12:23

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


void my_func(int sign_no)
{
    if(sign_no == SIGINT)
    {
        printf("i have get SIGINT.\n");
    }
    else if(sign_no == SIGQUIT)
    {
        printf("i have get SIGQUIT.\n");
    }
}

int main()
{
    printf("waiting for signal SIGINT or SIGQUIT.\n");

    // regist signal deal with funcion
    signal(SIGINT,my_func);
    signal(SIGQUIT,my_func);

    pause();
    exit(0);
    
    return 0;
}
