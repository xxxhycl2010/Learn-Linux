// A simple program that prints all its arguments.
// it does't use argc("argument count"); instand
// it takes advantage of the fact that the last
// value in argv ("argument count") is a null pointer.


#include <stdio.h>
#include <assert.h>

int main(int argc,char **argv)
{
    int i;
    printf("program name = \" %s \"\n",argv[0]);

    for( i=1;argv[i] !=NULL;++i)
    {
        printf("argv[%d] = \"%s\"\n",i,argv[i]);
        assert(i == argc);
    }
    return 0;
}
