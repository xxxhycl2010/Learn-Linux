// A simple program that test function of fwrite
// 2015-12-13 17:37:01

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define set_s(x,y) {strcpy(s[x].name,y);s[x].size=strlen(y);}

#define nmemb 3

struct test
{
    char name[20];
    int size;
}s[nmemb];

int main()
{
    FILE *stream;
    set_s(0,"linux!");
    set_s(1,"freebsd!");
    set_s(2,"window!");
    stream = fopen("/home/ycl/b.txt","w");
    fwrite(s,sizeof(struct test),nmemb,stream);
    fclose(stream);
    return 0;
}
