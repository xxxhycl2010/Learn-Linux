// A simple program that test how to use thread_mutex_lock
// 2015-12-19 10:30:21

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>


void fun_thread1(char *msg);
void fun_thread2(char *msg);

int g_value = 1;
pthread_mutex_t mutex;
//in the thread individual,the thread reset the g_value to 0,and add to 5
//int the thread1,add to 6 in the thread2

int main(int argc,char *argv[])
{
    pthread_t thread1;
    pthread_t thread2;
    if(pthread_mutex_init(&mutex,NULL) !=0 )
    {
        printf("init mutex error.\n");
        exit(1);
    }
    if(pthread_create(&thread1,NULL,(void*)fun_thread1,NULL) !=0)
    {
        printf("init thread1 error.\n");
        exit(1);
    }
    if(pthread_create(&thread2,NULL,(void*)fun_thread2,NULL)!=0)
    {
        printf("init thread2 error.\n");
        exit(1);
    }

    sleep(1);
    printf("i am main thread,g_value is %d\n",g_value);
    return 0;
}

void fun_thread1(char *msg)
{
    int val;
    val = pthread_mutex_lock(&mutex);
    if(val !=0)
    {
        printf("lock error.");
    }
    g_value = 0;
    printf("thread1 locked,init the g_value to 0,and add 5\n");
    g_value += 5;
    printf("the g_value is %d\n",g_value);
    pthread_mutex_unlock(&mutex);
    printf("thread1 unlocked.\n");
}

void fun_thread2(char *msg)
{
    int val;
    val = pthread_mutex_lock(&mutex);
    if(val != 0)
    {
        printf("lock error\n");
    }
    g_value = 0;
    printf("thread 2 locked,init the g_value to 0 and add 5.\n");
    g_value += 6;
    printf("the g_value is %d\n",g_value);
    pthread_mutex_unlock(&mutex);
    printf("thread 2 unlocked.\n");
}

