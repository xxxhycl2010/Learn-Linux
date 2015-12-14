// A simple program that test pipe
// the parent process by the pipeline to the string "hello\n" passed to the sub process and display
// 2015-12-14 21:01:08

#include <unistd.h>
#include <stdio.h>

int main()
{
    int filedes[2];
    char buffer[80];
    pipe(filedes);
    if(fork()> 0)
    {
        //parent process
        char s[] = "hello\n";
        write(filedes[1],s,sizeof(s));
    }
    else
    {
        //sub process
        read(filedes[0],buffer,80);
        printf("%s\n",buffer);
    }
}
