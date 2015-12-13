// A simple program that test function without buffer
// 2015-12-13 17:16:27

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int globe =4;
int main()
{
    pid_t pid;
    int vari = 5;
    printf("before fork\n");

    if((pid = fork()) < 0)
    {
        printf("fork error!\n");
        exit(0);
    }
    else if(pid == 0)
    {
        globe++;
        vari--;
        printf("child changed:\n");
    }
    else 
        printf("parent did not change! \n");

    printf("globe = %d ,vari = %d\n",globe,vari);
    exit(0);

    return 0;
}
