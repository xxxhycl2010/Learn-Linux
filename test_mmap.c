// A simple program that test mmap function
// the two processes share memory communication by mapping common files
// 2015-12-17 06:38:08

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[4];
    int age;
}people;

//map a normal file as shared mem;
int main(int argc,char *argv[])
{
    int fd,i;
    people *p_map;
    char temp;
    fd = open(argv[1],O_CREAT|O_RDWR|O_TRUNC,00777);
    lseek(fd,sizeof(people)*5-1,SEEK_SET);
    write(fd,"",1);

    p_map = (people*)mmap(NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);
    temp = 'a';
    for(i = 0;i<10;i++)
    {
        temp += 1;
        memcpy((*(p_map+1)).name,&temp,2);
        (*(p_map+1)).age = 20 + i;
    }

    printf("initialize over\n");
    sleep(10);
    munmap(p_map,sizeof(people)*10);
    printf("umap ok\n");
        
}

