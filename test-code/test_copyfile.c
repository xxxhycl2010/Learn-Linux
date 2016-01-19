// A simple program that test copy file 
// 2015-12-13 16:38:20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFFER_SIZE 1024

int main(int argc,char *argv[])
{
    int from_fd,to_fd;
    int bytes_read,bytes_write;
    char buffer[BUFFER_SIZE];
    char *ptr;

    if(argc !=3)
    {
        fprintf(stderr,"Usage:%s fromfile tofile \n\a",argv[0]);
        exit(1);
    }

    //open source file
    if((from_fd = open(argv[1],O_RDONLY)) == -1)
    {
        fprintf(stderr,"open %s error:%s\n",argv[1],strerror(errno));
        exit(1);
    }

    //create destination file
    if((to_fd = open(argv[2],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR)) == -1)
    {
        fprintf(stderr,"open %s error:%s\n",argv[2],strerror(errno));
        exit(1);
    }

    //the following code is the classic code of copy file
    while(bytes_read = read(from_fd,buffer,BUFFER_SIZE))
    {
        // a fatal error has occurred
        if((bytes_read == -1)&&(errno != EINTR)) break;
        else if(bytes_read>0)
        {
            ptr = buffer;
            while(bytes_write = write(to_fd,ptr,bytes_read))
            {
                // a fatal error has occurred
                if((bytes_write==-1)&&(errno !=EINTR)) break;
                // write down all the bytes of reading
                else if(bytes_write==bytes_read) break;
                //if write down the part of reading,and then continue
                else if(bytes_write>0)
                {
                    ptr += bytes_write;
                    bytes_read -= bytes_write;
                }
            }
            //a fatal error occured when it is writing down
            if(bytes_write == -1) break;
        }
    }
    close(from_fd);
    close(to_fd);
    exit(0);
    return 0;
}
