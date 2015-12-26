// A simple program that test concurrency server model
// this is a nulti thread solution
//Description: all the contents of the file on the server to the client
//2015-12-20
//notice:
//there are some bug with pthread_create funcion,that need to modify


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <pthread.h>

#define DEFAULT_SVR_PORT 2828
#define FILE_MAX_LEN  64

char filename[FILE_MAX_LEN + 1];

static void *handle_client(void *arg)
{
	int sock =*(int*)arg;
	char buff[1024];
	int len;
	printf("begin send.\n");
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		close(sock);
		exit(-1);
	}
	//send file name
	if (send(sock, filename, FILE_MAX_LEN, 0) == -1)
	{
		perror("send file name\n");
		goto EXIT_THREAD;
	}

	printf("begin send file %s...\n", filename);
	//send file content;
	while (!feof(file))
	{
		len = fread(buff, 1, sizeof(buff), file);
		printf("server read %s ,len %d\n", filename, len);
		if (send(sock, buff, len, 0) < 0)
		{
			perror("send file:");
			goto EXIT_THREAD;
		}
	}
EXIT_THREAD:
	if (file)
		fclose(file);
	close(sock);
}

	int main(int argc, char *argv[])
	{
		int sockfd, new_fd;
		struct sockaddr_in my_addr;
		struct sockaddr_in their_addr;
		int sin_size, numbytes;
		pthread_t cli_thread;
		unsigned short port;
		if (argc < 2)
		{
			printf("need a file name without path\n");
			exit(1);
		}
		strncpy(filename, argv[1], FILE_MAX_LEN);
		port = DEFAULT_SVR_PORT;
		if (argc >= 3)
		{
			port = (unsigned short)atoi(argv[2]);
		}

		//first: build tcp socket
		//AF_INET --->ip communications
		//SOCK_STREAM ---->TCP
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			perror("socket");
			exit(-1);
		}
		//second: set monitor port
		//initialized struct,and bind 2828 port
		memset(&my_addr, 0, sizeof(struct sockaddr));
		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(port);
		my_addr.sin_addr.s_addr = INADDR_ANY;
		//third: bind socket,and build ralation between socket queue and port
		if (bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1)
		{
			perror("bind");
			goto EXIT_MAIN;
		}
		//fourth:start monitor 2828
        //port to look whether client	send connect
		if (listen(sockfd, 10) ==	-1)
		{
			perror("listen");
			goto
				EXIT_MAIN;
		}
		printf("#@listen port %d\n",port);

		//fifth: loop and communicate  with client
		while (1)
		{
			sin_size = sizeof(struct sockaddr_in);
			printf("server  waiting ...\n");
			if ((new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size)) == -1)
			{
				perror("accept");
				goto
					EXIT_MAIN;
			}
			printf("------client( ip = %s :port =%d)request 	\n", inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port));
			pthread_create(&cli_thread, NULL, handle_client, (void*)new_fd);

		}

		//sixth:
		close(socket);
	EXIT_MAIN:
		close(sockfd);
		return
			0;



	}

