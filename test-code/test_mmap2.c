// A simple program that test mmap funcion
// 2015-12-17 06:53:59
//
//notice: it is relation with test_mmap.c file ,after run the object file
//of test_mmap.c, you can run this file
//eg:
// $ ./test_mmap temp.txt
// after it output "ok"
// run 
//  $ ./temp_mmap2 temp.txt
//  it will output the content of temp.txt file
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

typedef struct
{
    char name[4];
    int age;
}people;

int main(int argc,char *argv[])
{
    int fd,i;
    people *p_map;
    fd = open(argv[1],O_CREAT|O_RDWR,00777);

    p_map = (people*)mmap(NULL,sizeof(people)*10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    for(i =0;i<10;i++)
    {
        printf("name:%s,age:%d;\n",(*(p_map+1)).name,(*(p_map+1)).age);
    }

    munmap(p_map,sizeof(people)*10);

}


