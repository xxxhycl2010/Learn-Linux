// A simple program that test thread
// Description: achieve send parameter by creating thread
// 2015-12-19 09:57:30
// NOTICE: the pthread is not of the linux system library ,if you want to 
// compile and run c file ,you must add "-lpthread".
// eg: gcc filename -lpthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *create(void *arg)
{
    int *num;
    num = (int *)arg;
    printf("create parameter is %d\n",*num);
    return (void*)0;
}

int main(int argc,char *argv[])
{
    pthread_t tidp;
    int error;

    int test = 4;
    int *attr = &test;
    error = pthread_create(&tidp,NULL,create,(void*)attr);

    if(error)
    {
        printf("pthread_create is created is not created...\n");
        return -1;
    }

    sleep(1);
    printf("pthread_creat is created ...\n");
    return 0;
}
