#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "connectionHTTP.h"

void childProcess(Cmd cmd, int pipefdToChild[2], int pipefdToParent[2]){
	dup2(pipefdToChild[0], STDIN_FILENO);
	dup2(pipefdToParent[1], STDOUT_FILENO);
	
	if(execv("/usr/bin/env", cmd.cmdArgs) == -1)
	{
		perror("execv:");
		exit(EXIT_FAILURE);
	}
	return;
}
