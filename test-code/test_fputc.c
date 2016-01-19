// A simple program that test fputc function
// 2015-12-14 06:25:02

#include <stdio.h>

int main()
{
    FILE *fp;
    char a[26] = "abcdefghijklmnopqrstuvwxyz";
    int i;
    fp = fopen("/home/ycl/temp.txt","w");
    for(i=0;i<26;i++)
    {
        fputc(a[i],fp);
    }
    fclose(fp);

    return 0;
}
