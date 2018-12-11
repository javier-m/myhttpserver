#ifndef _PARSE_ARGS_
#define _PARSE_ARGS_

#define MIN_PORT_NO 1
#define MAX_PORT_NO ((1<<16) - 1)
#define DEFAULT_PORT 8080
#define DEFAULT_CMD_ARGS {"python3", "example/example.py"}


typedef struct
{
	int nbCmdArgs;
	char **cmdArgs;
} Cmd;

typedef struct
{
	int portNo;
	Cmd cmd;
} Args;

Args parseArgs(int argc, const char *argv[]);
int findTCPPort(char *c);
Cmd parseCmd(int argc, int argStart, const char *argv[]);

#endif
