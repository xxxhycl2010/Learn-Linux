// A simple program that test the rule of read and write pipe
// 2015-12-14 21:26:56

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



// the dependence of the writing end to read end
void test_fun_one()
{
    int pipe_fd[2];
    pid_t pid;
    char r_buf[4];
    char *w_buf;
    int writenum;
    int cmd;

    memset(r_buf,0,sizeof(r_buf));
    if(pipe(pipe_fd) < 0)
    {
        printf("pipe create error\n");
        return;
    }

    if((pid = fork()) == 0)
    {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        sleep(10);
        exit(-1);
    }
    else if(pid > 0)
    {
        sleep(1);
        close(pipe_fd[0]);
        w_buf = "111";
        if((writenum=write(pipe_fd[1],w_buf,4)) == -1)
        {
            printf("write to pipe error\n");
        }
        else
            printf("the bytes write to pipe is %d\n",writenum);

        close(pipe_fd[1]);
    }
}

// linux don't ensure varification of the automic nature of writing pipeline
void test_pipe_two()
{
   int pipe_fd[2];
   pid_t pid;
   char r_buf[4096];
   char w_buf[4096*2];
   int writenum;
   int rnum;
   memset(r_buf,0,sizeof(r_buf));
   if(pipe(pipe_fd)<0)
   {
        printf("pipe create error!\n");
        return;
   }
   if((pid = fork()) == 0)
   {
        close(pipe_fd[1]);
        while(1)
        {
            sleep(1);
            rnum = read(pipe_fd[0],r_buf,1000);
            printf("child:readnum is %d\n",rnum);
        }
        close(pipe_fd[0]);
        exit(0);
   }
   else if(pid > 0)
   {
        close(pipe_fd[0]);
        memset(r_buf,0,sizeof(r_buf));
        if((writenum=write(pipe_fd[1],w_buf,1024)) == -1)
        {
            printf("write to pipe error!\n");
        }
        else
        {
            printf("the bytes write to pipe is %d\n",writenum);
        }
        writenum = write(pipe_fd[1],w_buf,4096);
        close(pipe_fd[1]);
   }
}

int main()
{

//    test_fun_one();
    //fun two
    printf("test fun two:\n");
      test_pipe_two();
    return 0;
}
