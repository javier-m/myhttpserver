#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "parseArgs.h"

Args parseArgs(int argc, const char *argv[]){
	Args args;
	if (argc == 1)
	{
		args.portNo = DEFAULT_PORT;
		args.cmd = parseCmd(argc, 2, argv);
		return args;
	}
	if ((argc == 2) && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")))
	{
		printf("myhttpserver [-h]\n"
			   "myhttpserver [-p portNo][cmd]\n"
			   "myhttpserver with no arguments launch the server on port %i\n"
			   "with default command `python3 example/example.py`\n"
			   "`cmd` must be an installed binary accessible with `/usr/bin/env` with additional parameters\n"
			   "it should accept http request on its `stdin` and output http response on its `stdout`\n",
			   DEFAULT_PORT);
		exit(EXIT_SUCCESS);
	}
	if (!strcmp(argv[1], "-p"))
	{
		args.portNo = parseTCPPort((char *) argv[2]);
		args.cmd = parseCmd(argc, 3, argv);
		return args;
	}
	args.portNo = DEFAULT_PORT;
	args.cmd = parseCmd(argc, 1, argv);
	return args;
}


int parseTCPPort(char *c){
	int portNo;
	char *i = c;
	while (*c != '\0')
	{
		if (!isdigit(*c))
		{
			fprintf(stderr,
				    "the second argument should be an integer"
				    "in the range %i-%i\n", MIN_PORT_NO, MAX_PORT_NO);
		exit(EXIT_FAILURE);
		}
		c += 1;
	}
	portNo = atoi(i);
	if (portNo < MIN_PORT_NO && portNo > MAX_PORT_NO)
	{
		fprintf(stderr,
			   "the second argument should be an integer"
			   "in the range %i-%i\n", MIN_PORT_NO, MAX_PORT_NO);
		exit(EXIT_FAILURE);
	}
	return portNo;
}


Cmd parseCmd(int argc, int argStart, const char *argv[])
{
	Cmd cmd;
	int i_argc=argc, i_start=argStart;
	char **cmdArgs=(char **) argv, *defaultCmdArgs[] = DEFAULT_CMD_ARGS;
	if (argStart >= argc)
	{
		i_argc = 2;
		i_start = 0;
		cmdArgs = defaultCmdArgs;
	}
	cmd.nbCmdArgs = i_argc - i_start + 2;
	cmd.cmdArgs = (char **) malloc(cmd.nbCmdArgs);
	char *cmdArg, *env = "env";
	cmdArg = (char *) malloc(strlen(env) + 1);
	strncpy(cmdArg, env, strlen(env) + 1);
	*(cmd.cmdArgs) = cmdArg;
	for (int i=i_start; i<i_argc; ++i)
	{
		cmdArg = (char *) malloc(strlen(cmdArgs[i]) + 1);
		strncpy(cmdArg, cmdArgs[i], strlen(cmdArgs[i]) + 1);
		*(cmd.cmdArgs+i+1-i_start) = cmdArg;
	}
	*(cmd.cmdArgs+cmd.nbCmdArgs-1) = NULL;
	return cmd;
}
