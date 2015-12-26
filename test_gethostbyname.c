// A simple program that test conversion between name and address 
// 2015-12-19 11:12:41
// change www.baidu.com to ip address
// eg: #gcc test_gethostbyname.c
//     #./a.out www.baidu.com

#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>


int main(int argc,char **argv)
{
    char *ptr,**pptr;
    struct hostent *hptr;
    char str[32] = {'\0'};
    ptr = argv[1];      //eg: www.baidu.com
    if((hptr = gethostbyname(ptr)) == NULL)
    {
        printf("gethostbyname error for host:%s\n",ptr);
        return 0;
    }

    printf("official hostname:%s\n",hptr->h_name);
    for(pptr=hptr->h_aliases;*pptr != NULL;pptr++)
    {
        printf("alias:%s\n",*pptr);
    }
    switch(hptr->h_addrtype)
    {
        case AF_INET:
        case AF_INET6:
        pptr = hptr->h_addr_list;
        for(;*pptr!=NULL;pptr++)
        {
            printf("address :%s\n",inet_ntop(hptr->h_addrtype,*pptr,str,sizeof(str)));
            
        }
        printf("first address: %s\n",inet_ntop(hptr->h_addrtype,hptr->h_addr,str,sizeof(str)));
        break;
        default:
        printf("unknown address type\n");
        break;
    }

    return 0;
}

