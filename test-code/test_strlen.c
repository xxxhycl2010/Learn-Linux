//this is test custom strlen function and strcpy function

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
	
int strlen1(const char *b)
{
	int i=0;
	while(*b!='\0')
	{
		i++;
		b++;
	}
	return i;
}

char *strcpy1(char *p,const char *q)
{
    char *des = p;
    assert((p !=NULL) && (q!=NULL));
    while((*p=*q)!='\0')
    {
        p++;
        q++;
    }
    *p = '\0';
    return des;
}

int main()
{
    char *str = "abcdef";
    int length = 0;
    length = strlen1(str);
    printf("str length = %d\n",length);
    
    char *temp = "123";
    printf("temp = %s\n",temp);
    printf("*temp = %c\n",*temp);
    printf("sizeof(temp) = %d\n",(int)sizeof(temp));
    char clone[20];
    strcpy(clone, str);
    printf("clone = %s\n",clone);

    char *p = (char*)malloc(10*sizeof(char));
    strcpy1(p,str);

    printf("p str = %s\n",p);
    char *p1 =(char*)malloc(sizeof(char));
    strcpy(p1,str);

    printf("p1 str = %s\n",p1);
}

