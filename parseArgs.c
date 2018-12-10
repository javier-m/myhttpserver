#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "parseArgs.h"

int findHTTPport(int argc, const char *argv[]){
	if (argc == 1)
	{
		return DEFAULT_PORT;
	}
	if (argc == 2)
	{
		if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
		{
			printf("myhttpserver [-h]\n"
				   "myhttpserver [-p portNo]\n"
				   "myhttpserver with no arguments launch the server on port %i\n", DEFAULT_PORT);
			exit(EXIT_SUCCESS);
		} else
		{
			fprintf(stderr,
			        "wrong arguments: type `myhttpserver -h` to get help\n");
			exit(EXIT_FAILURE);
		}
	}
	if (argc !=3)
	{
		fprintf(stderr,
			   "wrong number of arguments: "
			   "2 expected, %i received\n", argc - 1);
		exit(EXIT_FAILURE);
	}
	if ((int) strlen(argv[1]) > 2 || strncmp(argv[1], "-p", 2))
	{
		fprintf(stderr,
			   "the first argument should be the flag `-p`\n");
		exit(EXIT_FAILURE);
	}
	char *c = (char *) *(argv+2);
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
	if (atoi(argv[2]) < MIN_PORT_NO \
		&& atoi(argv[2]) > MAX_PORT_NO)
	{
		fprintf(stderr,
			   "the second argument should be an integer"
			   "in the range %i-%i\n", MIN_PORT_NO, MAX_PORT_NO);
		exit(EXIT_FAILURE);
	}
	return atoi(argv[2]);
}