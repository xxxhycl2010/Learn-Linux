// A simple program that test fgetc function
// 2015-12-13 18:04:53

#include <stdio.h>

int main()
{
    FILE *fp;
    int c;
    fp = fopen("/home/ycl/temp.txt","r");
    while((c = fgetc(fp)) != EOF)
        printf("%c",c);
    fclose(fp);


    int a,i;
    for(i=0;i<5;i++)
    {
        a = getchar();
        putchar(a);
    }
    printf("\n");
    return 0;
}
