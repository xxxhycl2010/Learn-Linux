// A simple program that test function of create file
// 2015-12-13 16:23:12

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void create_file(char *filename)
{
    if(creat(filename,0755)<0)
    {
        printf("create file %s failure!\n",filename);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("create file %s success!\n",filename);
    }
}

int main(int argc, char *argv[])
{
    int i;
    if(argc <2)
    {
        perror("you haven't input the filename,please try again!\n");
        exit(EXIT_FAILURE);
    }
    for(i=1;i<argc;i++)
    {
        create_file(argv[i]);
    }
    exit(EXIT_SUCCESS);

    return 0;
}
