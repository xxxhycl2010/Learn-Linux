 /* A simple program that test UDP protocol model 
  * implemention of udp protocol transmission file
  * this is the server that file name is udp_net_server1.c
  * the relation client is named upd_net_server1.c
  * 2015-12-25 21:48:40
  * */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sfd == -1)
    {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in saddr;
    bzero(&saddr,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8888);
    saddr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sfd,(struct sockaddr*)&saddr,sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        close(sfd);
        exit(-1);
    }

    char buf[512] = {0};
    struct sockaddr_in fromaddr;
    bzero(&fromaddr,sizeof(fromaddr));
    int fromaddrlen = sizeof(struct sockaddr);
    if(recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&fromaddr,
                    &fromaddrlen) == -1)
    {
        perror("recvfrom");
        close(sfd);
        exit(-1);
    }

    printf("receive from %s %d,the message is :%s\n",
                inet_ntoa(fromaddr.sin_addr),ntohs(fromaddr.sin_port),buf);
    FILE *fp = fopen("/home/ycl/a.txt","rb");
    struct stat st;
    stat("/home/ycl/a.txt",&st);
    int filelen = st.st_size;
    sendto(sfd,(void*)&filelen,sizeof(int),0,(struct sockaddr*)&fromaddr,
                sizeof(struct sockaddr));
    while(!feof(fp))
    {
        int len = fread(buf,1,sizeof(buf),fp);
        sendto(sfd,buf,len,0,(struct sockaddr*)&fromaddr,sizeof(struct sockaddr));

    }

    close(sfd);

    return 0;

}
