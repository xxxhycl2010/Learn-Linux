/* A simple program that test multiplex medel 多路转接模型 
 * this file is achieve server named tcp_net_server2.c ,the raltion client
 * file is tcp_net_client2.c,
 * 2015-12-24 07:25:07
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

/* define port */
#define portnumber 8000
#define MAX_LINE 80

/* deal with the function,this is change char from upper letter to lower letter,the parameter is the string that need to transform */
void my_fun(char *p)
{
    if(p == NULL)
      return;
    for(;*p !='\0';p++)
    {
        if(*p >= 'A' && *p <= 'Z')
        {
            *p = *p -'A' + 'a';
        }
    }

}


int main(void)
{
    int lfd;
    int cfd;
    int sfd;
    int rdy;

    struct sockaddr_in sin;
    struct sockaddr_in cin;

    int client[FD_SETSIZE];
    int maxi;
    int maxfd;
    fd_set rset;
    fd_set allset;
    socklen_t addr_len;
    char buffer[MAX_LINE];
    int i;
    int n;
    int len;
    int opt = 1;
    char addr_p[20];
    
    /* assign a value to server_addr_in struct */
    bzero(&sin,sizeof(struct sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    //receive any ip address,and change ip address from ip to net bytes
    sin.sin_port = htons(portnumber);
 
    if((lfd=socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        fprintf(stderr,"socket error:%s\n",strerror(errno));
        exit(1);
    }   

    // set socket options,use default option
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    if(bind(lfd,(struct sockaddr*)(&sin),sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr,"bind error:%s\n",strerror(errno));
        exit(1);
    }

    if(listen(lfd,20) == -1)
    {
        fprintf(stderr,"listen error:%s\n",strerror(errno));
        exit(1);
    }

    printf("accepting connections .....\n");

    maxfd = lfd;
    maxi = -1;

    for(i=0;i<FD_SETSIZE;i++)
    {
        client[i] = -1;
    }

    FD_ZERO(&allset);
    FD_SET(lfd,&allset);

    while(1)
    {
        rset = allset;
        rdy = select(maxfd+1,&rset,NULL,NULL,NULL);
        if(FD_ISSET(lfd,&rset))
        {
            addr_len = sizeof(sin);
            if((cfd = accept(lfd,(struct sockaddr*)(&sin),&addr_len)) == -1)
            {
                fprintf(stderr,"accept error:%s\n",strerror(errno));
                exit(1);
            }

            for(i=0;i<FD_SETSIZE;i++)
            {
                if(client[i] <= 0)
                {
                    client[i] = cfd;
                    break;
                }
            }

            if(i == FD_SETSIZE)
            {
                printf("too many clients.\n");
                exit(1);
            }
            FD_SET(cfd,&allset);
            if(cfd > maxfd)
            {
                maxfd = cfd;
            }
            if(i>maxi)
            {
                maxi = i;
            }
            if(--rdy <= 0)
            {
                continue;
            }
        }

        for(i=0;i<FD_SETSIZE;i++)
        {
            if((sfd = client[i])<0)
            {
                continue;
            }
            if(FD_ISSET(sfd,&rset))
            {
                n = read(sfd,buffer,MAX_LINE);
                printf("%s\n",buffer);
                if(n == 0)
                {
                    printf("the other side has been close.\n");
                    fflush(stdout);
                    close(sfd);

                    FD_CLR(sfd,&allset);
                    client[i] = -1;
                }
                else
                {
                    inet_ntop(AF_INET,&cin.sin_addr,addr_p,sizeof(addr_p));
                    addr_p[strlen(addr_p)] = '\0';
                    printf("client ip is %s,port is %d\n",addr_p,ntohs(cin.sin_port));
                    my_fun(buffer); 
                    n = write(sfd,buffer,n+1);

                    if(n ==1)
                    {
                        exit(1);
                    }
                }
                if(--rdy <= 0)
                {
                    break;
                }
            }
        }
    }
    close(lfd);
    return 0;
}
