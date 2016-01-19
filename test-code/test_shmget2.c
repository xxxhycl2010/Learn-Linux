// A simple program that test read shared memory of system v
// notice : test_sheget.c create a shared memory
// test_shmget2.c read the shared memory
// 2015-12-19 09:27:53

#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>

typedef struct
{
    char name[4];
    int age;
}people;

int main(int argc,char **argv)
{
    int shm_id ,i;
    key_t key;
    people *p_map;
    char *name = "/dev/shm/myshm";
    key = ftok(name,0);
    if(key == -1)
        perror("ftok error.");
    shm_id = shmget(key,4096,IPC_CREAT);
    if(shm_id == -1)
    {
        perror("shmget error.");
        return -1;
    }

    p_map = (people*)shmat(shm_id,NULL,0);
    for(i=0;i<10;i++)
    {
        printf("name:%s\n",(*(p_map+i)).name);
        printf("age:%d \n",(*(p_map+i)).age);
    }

    if(shmdt(p_map) == -1)
    {
        perror("detach error.");
    }

    return 0;
}
