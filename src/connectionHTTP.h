#ifndef _CONNECTIONHTTP_H_
#define _CONNECTIONHTTP_H_

#include <netinet/in.h>

#include "parseArgs.h"

#define MAX_NB_THREADS 10
#define BACKLOG_LISTEN 3
#define BUFFER_SIZE 1024

typedef struct {
	int fd;
	struct sockaddr_in address;
	int addrlen;

} SocketStruct;

typedef struct
{
	int thread_id;
	int accepting_socket_fd;
	Cmd cmd;
} ThreadArgs;

void runServer(Args portNo);
SocketStruct createListeningSocket(int portNo);
void serveRequests(SocketStruct *listening_socket, Cmd cmd);
void *serveSingleRequest(void *threadArgs);
int createProcess(void);
void parentProcess(int accepting_socket_fd, int pipefdToChild[2], int pipefdToParent[2]);
void childProcess(Cmd cmd, int pipefdToChild[2], int pipefdToParent[2]);

#endif
