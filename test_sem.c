// A simple program that test application of signal lamps
//  semget,semop,semctl,
//  2015-12-16 21:09:16
///usr/include/linux/ipc.h 中有定义,但是 /usr/include/sys/ipc.h 中没有
//union semun {
//                  int val;
//                  struct semid_ds *buf;
//                  ushort *array;
//              }arg;
//                                                         而通常程序会包含 sys/ipc.h sys/sem.h 不可能去包含 linux/ipc.h, linux/sem.h, 否则不可能在unix 下通过apache 的http_main.c 中是自己增加semun的定义的。
//
// union   semun   
// {   
//       int   val;                     /*   value   for   SETVAL   */   
//      struct   semid_ds   *buf;      /*   buffer   for   IPC_STAT,   IPC_SET   */      
//      unsigned   short   *array;     /*   array   for   GETALL,   SETALL   */   
//                                                                             /*   Linux   specific   part:   */   
//  struct   seminfo   *_buf;         /*   buffer   for   IPC_INFO   */   
//                                                                          };
//
#include <stdio.h>
#include <sys/sem.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/msg.h>


#define SEM_PATH "/home/ycl/my_sem"
#define max_tries 3
int semid;

int main()
{
    int flag1,flag2,key,i,init_ok,tmperrno;
    struct semid_ds sem_info;
    struct seminfo sem_info2;
    union semun {
        int val;
        struct semid_ds *buf;
        ushort *array;
        struct   seminfo   *_buf;
    }arg;
    struct sembuf askfor_res,free_res;
    flag1 = IPC_CREAT|IPC_EXCL|00666;
    flag2 = IPC_CREAT|00666;
    key = ftok(SEM_PATH,'a');
    //error handing for ftok here;
    init_ok = 0;
    //create a semaphone set that only include one sempore.
    semid = semget(key,1,flag1);
    if(semid < 0)
    {
        tmperrno = errno;
        perror("semget");
        if(tmperrno == EEXIST)
        //errno is undefined after a successful library call
        //(including perror call) so it is saved in tmperrno;
        {
            semid = semget(key,1,flag2);
            arg.buf = &sem_info;
            for(i=0;i<max_tries;i++)
            {
                if(semctl(semid,0,IPC_STAT,arg) == -1)
                {
                    perror("semctl error.");
                    i = max_tries;
                }
                else
                {
                    if(arg.buf->sem_otime != 0)
                    {
                        i = max_tries;
                        init_ok = 1;
                    }
                    else
                    {
                        sleep(1);
                    }
                }
            }

            if(!init_ok)
            //do some initializing,here we assume that the first process 
            //that create the sem will finish initialize the sem and run
            //semop in max_tries*1 seconds.else it will not run semop
            //any more
            {
                arg.val = 1;
                if(semctl(semid,0,SETVAL,arg) == -1)
                    perror("semctl setval error");
            }
        }
        else
        {
            perror("semget error,process exit.");
            exit(1);
        }
    }
    else
    {
        arg.val =1;
        if(semctl(semid,0,SETVAL,arg)== -1)
        {
            perror("semctl seval error");
        }
    }
    //get some information about the semaphore and the limit of semaphore
    //in red hat8.0
    arg.buf = &sem_info;
    if(semctl(semid,0,IPC_STAT,arg) == -1)
    {
        perror("semctl ipc stat");
    }
    printf("owner's uid is %d\n",arg.buf->sem_perm.uid);
    printf("owner's gid is %d\n",arg.buf->sem_perm.gid);
    printf("create's uid is %d\n",arg.buf->sem_perm.cuid);
    printf("create's gid is %d\n",arg.buf->sem_perm.cgid);
    arg._buf = &sem_info2;
    // there are some error need to modify
    /*
    if(semctl(semid,0,IPC_INFO,arg) == -1)
    {
        perror("semctl ipc info");
    }
    */
    printf("the number of entries in semaphore map is %d\n",arg._buf->semmap);
    printf("max number of semaphore in dentifiers is %d\n",arg._buf->semmni);
    printf("mas number of semaphore in system is %d\n",arg._buf->semmns);
    printf("the number of undo structures system wide is %d\n",arg._buf->semmnu);
    printf("max number of semaphores per semid is %d\n",arg._buf->semmsl);
    printf("max number of ops per semop call is %d\n",arg._buf->semopm);
    printf("max number of undo entries per process is %d\n",arg._buf->semume);
    printf("the sizeof of struct sem_undo is %d\n",arg._buf->semusz);
    printf("the maximum semaphore value is %d\n",arg._buf->semvmx);
    //now ask for avaliable resource
    askfor_res.sem_num = 0;
    askfor_res.sem_op = -1;
    askfor_res.sem_flg = SEM_UNDO;

    if(semop(semid,&askfor_res,1) == -1)
        perror("semop error");
    sleep(3);
    printf("now free the resources.\n");

    //now free resource
    free_res.sem_num = 0;
    free_res.sem_op = 1;
    free_res.sem_flg = SEM_UNDO;
    if(semop(semid,&free_res,1) == -1)
    {
        if(errno == EIDRM)
            printf("the semaphore set was removed.\n");
    }

    if(semctl(semid,0,IPC_RMID) == -1)
    {
        perror("semctl IPC_RMID");
    }
    else
        printf("remove sem ok\n");

    return 0;
}
