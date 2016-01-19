// A simple program that test scanf functions ,include scanf,fscanf,sscanf
// 2015-12-14 06:58:40

#include <stdio.h>

int main()
{
    int i;
    unsigned int j;
    char s[5];
    fscanf(stdin,"%d %x %5[a-z] ",&i,&j,s);
    printf("%d %d %s \n",i,j,s);

    //sscanf function
    char input[] = "10 0x1b aaaaaaaa bbbbbbbb";
    sscanf(input,"%d %x %5[a-z] %s",&i,&j,s,s);

    printf("%d %d %s \n",i,j,s);
    return 0;
}
