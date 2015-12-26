// a simple program that test tcp net client
// the relation file is tcp_net_server1.c, you can use this as server
// this is cliet that receive file from server 
// 2015-12-22 22:27:41
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define FILE_MAX_LEN 64
#define DEFAULT_SVR__PORT 2828

int main(int argc,char *argv[])
{
    int sockfd,numbytes;
    char buf[1024],filename[FILE_MAX_LEN+1];
    char ip_addr[64];
    struct hostent *he;
    struct sockaddr_in their_addr;
    int i=0,len,total;
    unsigned short port;
    FILE *file = NULL;
    if(argc < 2)
    {
        perror("need a server ip \n");
        exit(-1);

    }

    strncpy(ip_addr,argv[1],sizeof(ip_addr));
    port = DEFAULT_SVR__PORT;
    if(argc >=3)
    {
        port = (unsigned short)atoi(argv[2]);

    }
    //DNS
    //he = gethostbyname(argv[1]);
    //first: build a socket 
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket");
        exit(1);

    } 
    //second: set the address and port(2828) of server
    memset(&their_addr,0,sizeof(their_addr));
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(port);
    their_addr.sin_addr.s_addr = inet_addr(ip_addr);
    //their_addr.sin_addr = *(struct in_addr*)he->h_addr;
    //bzero(&(their_addr.sin_zero),8);

    printf("connect server %s:%d\n",ip_addr,port);
    //third: use connect function to build connection with server,this 
    //is not use local port,and protoal stack will auto segment port
    if(connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr))== -1)
    {
        perror("connect");
        exit(1);

    }
    if(send(sockfd,"hello",6,0)< 0)
    {
        perror("send");
        exit(1);

    }
    //receive file name, to make the program easy,the first 64 bytes is the filename ,if it not enough,it will fill with 0
    total = 0;
    while(total<FILE_MAX_LEN)
    {
        len = recv(sockfd,filename+total,(FILE_MAX_LEN-total),0);
        if(len <= 0)
          break;
        total += len;


    }

    //receive file name error
    if(total != FILE_MAX_LEN)
    {
        perror("failure file name");
        exit(-3);

    }
    printf("recv file is %s...\n",filename);
    file = fopen(filename,"wb");
    //file = fopen("/home/ycl/abc.txt","wb");
    if(file == NULL)
    {
        printf("create file %s failure\n",filename);
        perror("create");
        exit(-3);

    }

    // receive file data
    printf("recv begin \n");
    total = 0;
    while(1)
    {
        len = recv(sockfd,buf,sizeof(buf),0);
        if(len == -1)
        {
            break;

        }
        total += len;
        fwrite(buf,1,len,file);
    }
    fclose(file);
    printf("recv file %s success total length %d\n",filename,total);
    //fourth: colse socket
    close(sockfd);


}

//note: when you read many data of file ,the followding code is efficient
/* read many content */
ssize_t readn(int fd,char *buf,int size)
{
    char *pbuf = buf;
    int total,nread;
    for(total =0;total<size;)
    {
        nread = read(fd,pbuf,size-total);
        if(nread == 0)
          return total;
        if(nread == -1)
        {
            if(errno == EINTR)
              continue;
            else
              return -1;
        }
        total += nread;
        pbuf += nread;

    }
    return total;

}

/* write many content */
ssize_t writen(int fd,char *buf,int size)
{
    char *pbuf = buf;
    int total,nwrite;
    for(total = 0;total<size;)
    {
        nwrite = write(fd,pbuf,size-total);
        if(nwrite <= 0)
        {
            if(nwrite == -1 && errno == EINTR)
              continue;
            else
              return -1;
        }
        total += nwrite;
        pbuf += nwrite;
    }
    return total;
}
