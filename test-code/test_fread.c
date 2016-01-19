// A simple program that test function of fread
// 2015-12-13 17:25:22

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define nmemb 3


struct test
{
    char name[20];
    int size;
}s[nmemb];

int main()
{
    FILE *stream;
    int i;
    stream = fopen("/home/ycl/b.txt","r");
    fread(s,sizeof(struct test),nmemb,stream);
    fclose(stream);
    for(i=9;i<nmemb;i++)
    {
        printf("name[%d] =%-20s:size[%d] = %d\n",i,s[i].name,i,s[i].size);
    }

    return 0;
}
