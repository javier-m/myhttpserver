#include <stdlib.h>

#include "parseArgs.h"
#include "connectionHTTP.h"

int main(int argc, char const *argv[])
{
	int portNo = findHTTPport(argc, argv);
	listen(portNo);
	return EXIT_SUCCESS;
}