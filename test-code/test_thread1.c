// A simple program that test create thread
// description: create two thread and realize every 1s to achieve a print
// 2015-12-19 09:42:01
// notice: the pthread library is not of linux system library,so when you
// compile and run c file ,you must add "-lpthread",
// eg: gcc filename -lpthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void *myThread1(void)
{
    int i;
    for(i=0;i<100;i++)
    {
        printf("this is the lst pthread,created by rieckey.\n");
        sleep(1);
    }
}

void *myThread2(void)
{
    int i;
    for(i=0;i<10;i++)
    {
        printf("this is the 2st pthread,created by zieckey.\n");
        sleep(1);
    }
}

int main()
{
    int i = 0,ret = 0;
    pthread_t id1,id2;

    //create thread one
    ret = pthread_create(&id1,NULL,(void*)myThread1,NULL);
    if(ret)
    {
        printf("create pthread error.\n");
        return 1;
    }

    //create thread two
    ret = pthread_create(&id2,NULL,(void*)myThread2,NULL);
    if(ret)
    {
        printf("create pthread error!\n");
        return 1;
    }

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);

    return 0;
}
