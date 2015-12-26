#include "tcp_net_socket.h"

int tcp_init(const char *ip,int port)
{
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd == -1)
    {
        perror("socket");
        exit(-1);
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(struct sockaddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(ip);
    if(bind(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        close(sfd);
        exit(-1);
    }

    if(listen(sfd,10) == -1)
    {
        perror("listen");
        close(sfd);
        exit(-1);
    }
    return sfd;
}

int tcp_accept(int sfd)
{
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
    printf("%s %d success connect...\n",inet_ntoa(clientaddr.sin_addr),
            ntohs(clientaddr.sin_port));

    return new_fd;
}

int tcp_connect(const char *ip,int port)
{
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd == -1)
    {
        perror("scoket");
        exit(-1);
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(struct sockaddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(ip);
    if(connect(sfd,(struct sockaddr*)&serveraddr,sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        close(sfd);
        exit(-1);
    }
    return sfd;
}

void signalhandler(void)
{
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset,SIGINT);
    sigaddset(&sigset,SIGQUIT);
    sigprocmask(SIG_BLOCK,&sigset,NULL);
}
