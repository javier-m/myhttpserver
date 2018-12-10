#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "connectionHTTP.h"

void childProcess(int pipefdToChild[2], int pipefdToParent[2]){
	char request[BUFFER_SIZE] = {0};
	read(pipefdToChild[0], request, BUFFER_SIZE);
	char reply[BUFFER_SIZE] = {0};
	char body[BUFFER_SIZE];
	sprintf(body,
		    "<!doctype html>\n"
	        "<html>\n"
	        "<body>\n"
	        "<div>YOUR REQUEST</div>\n"
	        "<div>\n"
	        "%s"
	        "</div>\n"
	        "</body>\n"
	        "</html>\n",
	        request);
	char header[BUFFER_SIZE];
	sprintf(header,
		    "HTTP/1.1 200 OK\n"
	        "Content-Length: %i\n"
	        "Content-Type: text/html\n"
	        "\n",
	        (int) strlen(body));
	strcat(reply, header);
	strcat(reply, body);
	write(pipefdToParent[1], reply, strlen(reply));
	return;
}
