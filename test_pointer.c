#include <stdio.h>

int main()
{
	int *p;
	int i;
	i = 5;
	p = &i;
	printf("i = %d,p = %p,*p = %d\n",i,p,*p);
	*p = 6;
	printf("i = %d,p = %p,*p = %d\n",i,p,*p);
}
