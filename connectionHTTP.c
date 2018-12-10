#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

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
    // if (setsockopt(listening_socket.fd,
    // 	           SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
    //                &opt,
    //                sizeof(opt))) 
    // { 
    //     perror("setsockopt"); 
    //     exit(EXIT_FAILURE); 
    // } 
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
	int accepting_socket_fd;
	ssize_t nbBytesRead;
	if ((accepting_socket_fd = accept(listening_socket->fd,
		                              (struct sockaddr *) &(listening_socket->address),  
                                      (socklen_t*) &(listening_socket->addrlen)))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    }
    char buffer[BUFFER_SIZE] = {0}, *reply = "Hello World";
    // TODO
    // not thread safe!!! printf could be interleaved
    // should work by chunks of BUFFER_SIZE
    // connect to stdin/stdout of another application
    nbBytesRead = read(accepting_socket_fd, buffer, BUFFER_SIZE); 
    printf(">>> INCOMING REQUEST:\n%s\n\n", buffer); 
    send(accepting_socket_fd , reply , strlen(reply) , 0); 
    printf("<<< REPLY SENT:\n%s\n\n", reply);
}