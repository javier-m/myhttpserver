#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "connectionHTTP.h"


void runServer(int portNo){
	SocketStruct listening_socket = createListeningSocket(portNo);
	printf("listening on 0.0.0.0:%i...\n\n", portNo);
	serveRequests(&listening_socket);
}


SocketStruct createListeningSocket(int portNo){
	SocketStruct listening_socket;
	int opt = 1; 

	// Creating socket file descriptor 
    if ((listening_socket.fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    }
	// Forcefully attaching socket to the port `portNo` 
    if (setsockopt(listening_socket.fd,
    	           SOL_SOCKET, SO_REUSEPORT, 
                   &opt,
                   sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    listening_socket.address.sin_family = AF_INET; 
    listening_socket.address.sin_addr.s_addr = INADDR_ANY; 
    listening_socket.address.sin_port = htons(portNo);
    listening_socket.addrlen = sizeof(struct sockaddr_in);

    // Forcefully attaching socket to the port `portNo` 
    if (bind(listening_socket.fd,
    	     (struct sockaddr *) &listening_socket.address,  
             listening_socket.addrlen) < 0)
    {
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }
    if (listen(listening_socket.fd, BACKLOG_LISTEN) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    return listening_socket;
}


void serveRequests(SocketStruct *listening_socket){
	int inParent = 1;
	int nbConnection = 0;
	while(inParent)
	{
		// accept connection
		int accepting_socket_fd;
		if ((accepting_socket_fd = accept(listening_socket->fd,
			                              (struct sockaddr *) &(listening_socket->address),  
	                                      (socklen_t*) &(listening_socket->addrlen)))<0) 
	    { 
	        perror("accept"); 
	        exit(EXIT_FAILURE); 
	    }

	    // create pipes parent <-> child
	    int pipefdToChild[2], pipefdToParent[2];
	    if (pipe(pipefdToChild) != 0)
	    {
	    	perror("pipe:");
			exit(EXIT_FAILURE);

	    }
	    if (pipe(pipefdToParent) != 0)
	    {
	    	perror("pipe:");
			exit(EXIT_FAILURE);

	    }

	    // create child process
	    int pid = createProcess();
	    switch (pid) {
			case 0:
				close(pipefdToChild[1]);
				close(pipefdToParent[0]);
				inParent = 0;
				childProcess(pipefdToChild, pipefdToParent);
				break;
			default:
				close(pipefdToChild[0]);
				close(pipefdToParent[1]);
				printf("connection #%i\n", ++nbConnection);
				parentProcess(accepting_socket_fd, pipefdToChild, pipefdToParent);
				break;
		}
	}
}


int createProcess(void){
	int pid;
	do
		pid = (int) fork();
	while(pid == -1 && errno == EAGAIN);
	if(pid == -1 && errno != EAGAIN)
	{
		perror("fork:");
		exit(EXIT_FAILURE);
	}
	return pid;
}


void parentProcess(int accepting_socket_fd, int pipefdToChild[2], int pipefdToParent[2]){
    /*TODO
    not thread safe!!! printf could be interleaved
    should work by chunks of BUFFER_SIZE
    connect to stdin/stdout of another application*/
    // get request
    char request[BUFFER_SIZE] = {0};
    read(accepting_socket_fd, request, BUFFER_SIZE);
    write(pipefdToChild[1], request, BUFFER_SIZE);
    // get reply
    char reply[BUFFER_SIZE] = {0};
    int nbBytesRead;
    nbBytesRead = read(pipefdToParent[0], reply, BUFFER_SIZE);
    send(accepting_socket_fd, reply, nbBytesRead, 0); 
    int childStatus;
    if (wait(&childStatus) == -1)
    {
		perror("wait:");
		exit(EXIT_FAILURE);
    }
}