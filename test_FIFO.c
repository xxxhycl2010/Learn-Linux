// A simple program that test named pipeline or FIFO
// 2015-12-15 06:33:35

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


#define FIFO_SERVER "/home/ycl/fifoserver"

void test_fifo_one()
{
    int fd;
    char w_buf[4096*2];
    int real_wnum;

    memset(w_buf,0,4096*2);
    if((mkfifo(FIFO_SERVER,O_CREAT|O_EXCL) < 0 &&(errno != EEXIST)))
    {
        printf("cannot create fifoserver!\n");
    }

    //set non blocking flag
    fd = open(FIFO_SERVER,O_WRONLY|O_NONBLOCK,0);
    if(fd == -1)
    {
        if(errno == ENXIO)
            printf("write to fifo error:try later:\n");
    }
    else
        printf("real write num is %d\n",real_wnum);

    real_wnum = write(fd,w_buf,5000);
    if(real_wnum == -1)
    {
        if(errno == EAGAIN)
            printf("try later\n");
    }
}

void test_fifo_two(char *argv[])
{
    char r_buf[4096*2];
    int fd;
    int r_size;
    int ret_size;
    r_size = atoi(argv[1]);
    printf("requred real read bytes %d\n",r_size);
    memset(r_buf,0,sizeof(r_buf));
    fd = open(FIFO_SERVER,O_RDONLY|O_NONBLOCK,0);
    // this can compile two versin :block and non block
    if(fd == -1)
    {
        printf("open %s for error.",FIFO_SERVER);
        exit(0);
    }
    while(1)
    {
        memset(r_buf,0,sizeof(r_buf));
        ret_size = read(fd,r_buf,r_size);
        if(ret_size == -1)
            if(errno == EAGAIN)
                printf("no data avlaible.\n");
        printf("real read bytes %d\n",ret_size);
        sleep(1);
    }

    pause();
    unlink(FIFO_SERVER);
}


int main(int argc,char *argv[])
{
    
    //test one;
   // test_fifo_one();

    //test two:
    test_fifo_two(argv);
    return 0;

}
