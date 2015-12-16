// A simple program that test application of message queue
// 2015-12-16 06:34:39

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/types.h>


void msg_stat(int ,struct msqid_ds);

int main()
{
    int gflags,sflags,rflags;
    key_t key;
    int msgid;
    int reval;

    struct msgsbuf
    {
        int mtype;
        char mtext[1];
    }msg_sbuf;
    struct msgmbuf
    {
        int mtype;
        char mtext[10];
    }msg_rbuf;

    struct msqid_ds msg_ginfo,msg_sinfo;
    char *msgpath = "/home/ycl/msgqueue";
    key = ftok(msgpath,'a');
    gflags = IPC_CREAT|IPC_EXCL;
    msgid = msgget(key,gflags|00666);
    if(msgid == -1)
    {
        printf("msg create error\n");
        return -1;
    }

    //it will output default property of msg queue after creating one msg queue
    msg_stat(msgid,msg_ginfo);
    sflags = IPC_NOWAIT;
    msg_sbuf.mtype = 10;
    msg_sbuf.mtext[0] = 'a';
    reval = msgsnd(msgid,&msg_sbuf,sizeof(msg_sbuf.mtext),sflags);
    if(reval == -1)
    {
        printf("message send error:\n");
    }

    //it will output default property of msg queue after sending one msg
    msg_stat(msgid,msg_ginfo);
    rflags = IPC_NOWAIT|MSG_NOERROR;
    reval = msgrcv(msgid,&msg_rbuf,4,10,rflags);
    if(reval == -1)
    {
        printf("read msg error\n");
    }
    else
    {
        printf("read from msg queue %d bytes.\n",reval);
    }

    //it will output default property of msg queue after reading msg from msg queue
    msg_stat(msgid,msg_ginfo);
    msg_sinfo.msg_perm.uid = 8;
    msg_sinfo.msg_perm.gid = 8;
    msg_sinfo.msg_qbytes = 16388;

    //this code is verificate the root user who can modify dafault msg_qbytes of msg queue
    //notice: the set value is greater than default value

    reval = msgctl(msgid,IPC_SET,&msg_sinfo);
    if(reval == -1)
    {
        printf("msg set info error.\n");
        return -1;
    }
    msg_stat(msgid,msg_sinfo);
    // verificate set the property of msg queue
    reval = msgctl(msgid,IPC_RMID,NULL);    //remove msg queue
    if(reval == -1)
    {
        printf("unlink msg queue error.\n");
        return -1;
    }

    return 0;

}

void msg_stat(int msgid,struct msqid_ds msg_info)
{
    int reval;
    sleep(1);
    reval = msgctl(msgid,IPC_STAT,&msg_info);
    if(reval == -1)
    {
        printf("get msg info error.\n");
        return;
    }
    printf("\n");
    printf("current number of bytes on queue is %d\n",(int)msg_info.msg_cbytes);
    printf("number of message is queue is %d\n",(int)msg_info.msg_qnum);
    printf("max number of bytes on queue is %d\n",(int)msg_info.msg_qbytes);
    printf("pid of last msgsnd is %d\n",msg_info.msg_lspid);
    printf("pid of last msgrcv is %d\n",msg_info.msg_lrpid);
    printf("last msgsnd time is %s\n",ctime(&(msg_info.msg_stime)));
    printf("last msgrcv time is %s\n",ctime(&(msg_info.msg_rtime)));
    printf("last change time is %s\n",ctime(&(msg_info.msg_ctime)));
    printf("msg uid is %d\n",msg_info.msg_perm.uid);
    printf("msg gid is %d\n",msg_info.msg_perm.gid);
}
