#include <stdio.h>
#include <stdlib.h>
#include <error.h>

//display error and terminate
void exit_with_error_msg(const char* msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}