#ifndef _CONNECTIONHTTP_H_
#define _CONNECTIONHTTP_H_

#include <netinet/in.h>

#define BACKLOG_LISTEN 3
#define BUFFER_SIZE 1024


typedef struct {
	int fd;
	struct sockaddr_in address;
	int addrlen;

} SocketStruct;

void runServer(int portNo);
SocketStruct createListeningSocket(int portNo);
void serveRequests(SocketStruct *listening_socket);


#endif