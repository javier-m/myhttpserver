#ifndef _PARSE_ARGS_
#define _PARSE_ARGS_

#define MIN_PORT_NO 1
#define MAX_PORT_NO ((1<<16) - 1)
#define DEFAULT_PORT 8080

int findHTTPport(int argc, const char *argv[]);

#endif