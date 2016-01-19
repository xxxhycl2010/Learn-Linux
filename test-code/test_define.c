// A simple program that test how to use define
// 2015-12-13 10:27:04

#include <stdio.h>
#include <malloc.h>

#define NUM ok


//there are some common define

#ifndef COMDEF_H
#define COMDEF_H

#endif

#define MEM_B(x) (*((byte*)(x)))
#define MEM_W(x) (*((word*)(x)))

#define MAX(x,y) (((x)>(y))?(x):(y))
#define MIN(x,y) (((x)<(y))?(x):(y))

#define WARN_IF(EXP) \
do{ \
    if(EXP) \
    fprintf(stderr,"Warning:" #EXP "\n"); \
}while(0)



int main()
{
    struct stu
    {
        int num;
        char *name;
        char sex;
        float score;
    }*ps;
    ps = (struct stu*)malloc(sizeof(struct stu));
    ps->num = 102;
    ps->name = "jeremy";
    ps->sex = 'm';
    ps->score = 34;

#ifdef NUM
    printf("name = %s\n,score = %f\n",ps->name,ps->score);
#else
    printf("name=%s\n,sex=%c\n",ps->name,ps->sex);
#endif

    float a= 10;
    int b= 0;
    WARN_IF(b==0);
    printf("result = %f\n",a/b);

    return 0;
}
