#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

struct account user; //user struct
struct account tmp_entry; //temp struct
struct notice note;

//display error and terminate
void exit_with_error_msg(const char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
