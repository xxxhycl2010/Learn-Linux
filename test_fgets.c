// A simple program that test fgets function
// 2015-12-14 06:37:58

#include <stdio.h>
#include <string.h>

int main()
{
    FILE *stream;
    char string[] = "this is a test";
    char msg[20];
    //open a file for update
    stream = fopen("/home/ycl/temp.txt","w+");
    //write a string into the file
    fwrite(string,strlen(string),1,stream);
    //seek to the start of the file
    fseek(stream,0,SEEK_SET);
    //read a string from the file
    fgets(msg,strlen(string)+1,stream);
    //display the string
    printf("%s\n",msg);
    fclose(stream);
    
    return 0;
}
