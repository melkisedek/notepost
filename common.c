#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "common.h"

//display error and terminate
void exit_with_error_msg(const char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

char * get_string(){
    unsigned int len_max = 128;
    unsigned int current_size = 0;

    char *pStr = malloc(len_max);
    current_size = len_max;
    if(pStr != NULL)
    {
    	int c = EOF;
    	unsigned int i =0;
        //accept user input until hit enter or end of file
    	while (( c = getchar() ) != '\n' && c != EOF)
    	{
    		pStr[i++]=(char)c;
    		//if i reached maximize size then realloc size
    		if(i == current_size)
    		{
                current_size = i+len_max;
    			pStr = realloc(pStr, current_size);
    		}
    	}
    }
    return pStr;
}
