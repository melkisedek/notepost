#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <getopt.h>

/* Name of the running program*/
char *program_name;

/* Description of long options for getopt_long. */
/*1 is for options that take an argument e.g. -u myusername*/
static const struct option long_options[] = {
	// { "username",      1, NULL, 'u' },
	// { "password",      1, NULL, 'p' },
	{ "help",          0, NULL, 'h' },
	{ "version",       0, NULL, 'v' },
};


/* Description of short options for getopt_long. 
	: for option that expect arguments when specified*/

//static const char* const short_options = "u:p:hv";
static const char* const short_options = "hv";
/* Usage summary text. */

static const char* const usage_template =
"Usage: %s [ options ]\n"
// "-u, --username USERNAME    Specify a username.\n"
// "-p, --password PASSWORD    Specify password.\n"
"-h, --help                 Print this information.\n"
"-v, --version              Print version information.\n";


/* Print usage information and exit. If IS_ERROR is nonzero, write to
	stderr and use an error exit code. Otherwise, write to stdout and
	use a non-error termination code. Does not return. */

static void print_usage (int is_error)
{
	fprintf (is_error ? stderr : stdout, usage_template, program_name);
	exit (is_error ? 1 : 0);
}

//display error and terminate
void error(const char* msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

/*This function runs when someone presses CRL-C
*/
void handle_shutdown(int sig){
	fprintf(stderr, "\nGood Bye!\n");
	exit(0);
}

FILE *userfile;//usernames, passwords
FILE *notefile;//notes

#endif