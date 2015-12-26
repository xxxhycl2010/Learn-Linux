// A simple program that test TCP protocol
// Implementation of TCP protocol using C/S protocol
// 2015-12-19 15:49:27

#ifndef _TCP_NET_SOCKET_H
#define _TCP_NET_SOCKET_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

extern int tcp_init(const char *ip,int port);
extern int tcp_accept(int sfd);
extern int tcp_conect(const char *ip,int port);
extern void signalhandler(void);

#endif
