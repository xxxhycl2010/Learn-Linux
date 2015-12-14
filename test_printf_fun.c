// A simple program that test printf function ,include printf,fprintf,sprintf
// 2015-12-14 06:49:14


#include <stdio.h>
int main()
{

    int i=150;
    int j = -100;
    double k = 3.14243345;
    //printf function
    printf("%d %f %x\n",j,k,i);
    printf("%2d, %*d\n",i,2,i);

    //fprintf function
    fprintf(stdout,"%d %f %x\n",j,k,i);
    fprintf(stdout,"%2d %*d\n",i,2,i);

    //sprintf function
    char *a = "this is string A!";
    char buf[80];
    sprintf(buf,">>> %s <<<\n",a);
    printf("%s",buf);
    return 0;
}

