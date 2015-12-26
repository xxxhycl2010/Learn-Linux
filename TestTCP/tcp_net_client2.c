// A simple program that test tcp client
// the server is named tcp_net_server2.c ,this is client that named 
// tcp_net_client2.c
// 2015-12-24 22:18:59

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define portnumber 8000

int main(int argc,char *argv[])
{
    int nbytes;
    int sockfd;
    char buffer[80];
    char buffer_2[80];
    struct sockaddr_in server_addr;
    struct hostent *host;

    if(argc !=2)
    {
        fprintf(stderr,"usage:%s hostname \n",argv[0]);
        exit(1);
    }

    if((host = gethostbyname(argv[1])) == NULL)
    {
        fprintf(stderr,"gethostbyname error\n" );
        exit(1);
    }

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        fprintf(stderr,"socket error:%s\n",strerror(errno));
        exit(1);
    }
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portnumber);
    server_addr.sin_addr = *((struct in_addr*)host->h_addr);
    if(connect(sockfd,(struct sockaddr*)(&server_addr),sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr,"connect error:%s\n",strerror(errno));
        exit(1);
    }
    while(1)
    {
        printf("please input char:\n");
        fgets(buffer,1024,stdin);
        write(sockfd,buffer,strlen(buffer));
        if((nbytes= read(sockfd,buffer_2,81)) == -1)
        {
            fprintf(stderr,"read error:%s\n",strerror(errno));
            exit(1);
        }
        buffer_2[nbytes] = '\0';
        printf("client received from server %s\n",buffer_2);
    }
    close(sockfd);
    exit(0);
}
