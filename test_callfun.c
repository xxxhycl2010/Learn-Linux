// A simple program that test call function
// 2015-12-13 10:46:42

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


typedef struct list
{
    void *value_address;
    struct list *next;
}NODE;

NODE *Search_List(NODE *node,int(*compare)(void const *,void const *),
        void const *desired_value)
{
    while(node != NULL)
    {
        if(compare((node->value_address),desired_value) == 0)
        {
            break;

        }
        node = node->next;
    }

    return node;
}


int int_compare(void const *a,void const *b)
{
    if(*(int*)a == *(int*)b)
    {
        return 0;
    }
    else
        return -1;
}

NODE  *createList(int a[],int n)
{
    NODE *list;
    NODE *p,*q;
    q = NULL;
    int i;

    list = (NODE*)malloc(sizeof(NODE));
    if(list == NULL)
    {
        printf("malloc memory is fail!\n");
        exit(-1);
    }

    list->next = NULL;
    p = list;
    for(i=0;i<n;i++)
    {
        q = (NODE*)malloc(sizeof(NODE));
        if(q == NULL)
        {
            printf("malloc memory is fail!\n");
            exit(-1);
        }
        q->value_address = &a[i];
        p->next = q;
        p = q;
    }
    p->next = NULL;

    return list;

}

void traverse(NODE *list)
{
    if(list != NULL)
    {
        NODE *q = list->next;
        while(q!=NULL)
        {
            printf("%d \n",*(int*)q->value_address);
            q = q->next;
        }
    }
}

int main()
{
    int a[5] = {1,3,6,9,8};
    NODE *list = createList(a,5);
    traverse(list);
    printf("search value 6:\n");
    int desired_int_value = a[2];
    // there are some error that don't solve
    NODE *desired_node = Search_List(list,int_compare,&desired_int_value);
    printf("value = %d,next = %p\n",*(int*)desired_node->value_address,desired_node->next);
    return 0;
}
