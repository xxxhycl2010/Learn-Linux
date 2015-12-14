// A simple program that test mkfifo function and create Named pipe or FIFO
// 2015-12-14 22:13:09

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


#define FIFO "/home/ycl/2"

int main()
{
    char buffer[80];
    int fd;
    unlink(FIFO);
    mkfifo(FIFO,0666);
    if(fork() > 0)
    {
        char s[] = "hello\n";
        fd = open(FIFO,O_WRONLY);
        write(fd,s,sizeof(s));
        close(fd);
    }
    else
    {
        fd = open(FIFO,O_RDONLY);
        read(fd,buffer,80);
        printf("%s",buffer);
        close(fd);
    }

    return 0;
}
