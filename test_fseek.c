// A simple program that test fseek function
// 2015-12-13 17:46:37
//

#include <stdio.h>
#include <string.h>

int main()
{
    FILE *stream;
    long offset;
    // there are some bug that need to be modifyed
    fpos_t pos;
    stream=fopen("etc/paswd","r");
    fseek(stream,5,SEEK_SET);
    printf("offset=%f\n",(float)ftell(stream));
    rewind(stream);
    fgetpos(stream,&pos);
    printf("offset=%f\n",pos);
    pos = 10;

    fsetpos(stream,&pos);
    printf("offset = %d\n",ftell(stream));
    fclose(stream);

    return 0;
}
