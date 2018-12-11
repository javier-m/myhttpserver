#include <stdlib.h>

#include "parseArgs.h"
#include "connectionHTTP.h"

int main(int argc, char const *argv[])
{
	Args args = parseArgs(argc, argv);
	runServer(args);
	return EXIT_SUCCESS;
}
