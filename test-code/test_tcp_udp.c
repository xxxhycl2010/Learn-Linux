// A simple program that test TCP  and UDP 
//2015-12-19 15:00:57

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>


int main()
{
    //example 1
    
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd == -1)
    {
        perror("socket");
        exit(-1);
    }
    printf("sfd = %d\n",sfd);

    //exmaple 2
    /*
    struct sockaddr_in my_addr;
    memset(&my_addr,0,sizeof(struct sockaddr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8888);
    my_addr.sin_addr.s_addr = inet_addr("192.168.0.101");
    if(bind(sfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        close(sfd);
        exit(-1);
    }
*/

    //example 3
/*
    if(listen(sfd,10) == -1)
    {
        perror("listen");
        close(sfd);
        exit(-1);
    }
*/
    //example 4
    
    //receive request
    struct sockaddr_in clientaddr;
    memset(&clientaddr,0,sizeof(struct sockaddr));
    int addrlen = sizeof(struct sockaddr);
    int new_fd = accept(sfd,(struct sockaddr*)&clientaddr,&addrlen);
    if(new_fd == -1)
    {
        perror("accept");
        close(sfd);
        exit(-1);
    }

    printf("%s %d success connect\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));


    //example 5
    /*
    //connect server
    struct sockaddr_in seraddr;
    memset(&seraddr,0,sizeof(struct sockaddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(8888);
    seraddr.sin_addr.s_addr = inet_addr("192.168.0.101");
    if(connect(sfd,(struct sockaddr*)&seraddr,sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        close(sfd);
        exit(-1);
    }
*/

    //example 6
    //send data
    if(send(new_fd,"hello",6,0) == -1)
    {
        perror("send");
        close(new_fd);
        close(sfd);
        exit(-1);
    }


    //example 7
    //receive data
    char buf[512] = {0};
    if(recv(new_fd,buf,sizeof(buf),0) == -1)
    {
        perror("recv");
        close(new_fd);
        close(sfd);
        exit(-1);
    }
    puts(buf);
}
