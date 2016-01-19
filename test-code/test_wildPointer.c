//A simple program that test wild pointer
//2015-12-13 10:08:07

#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main()
{
    char *p = (char*)malloc(sizeof( char));
    strcpy(p,"hello");
    printf("addr = %p\n",p);
    printf("p = %s\n",p);
    free(p);

    printf("free after;\n");
    printf("addr = %p\n",p);
    if(p!=NULL)
    {
        strcpy(p,"world");
        
        printf("p = %s\n",p);
    }

    return 0;

}
