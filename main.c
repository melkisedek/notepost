#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>//file status
#include <unistd.h>

/* Description of long options for getopt_long. */
/*1 is for options that take an argument e.g. -u myusername*/
static const struct option long_options[] = {
	{ "username",      1, NULL, 'u' },
	{ "password",         1, NULL, 'p' },
	{ "help",         0, NULL, 'h' },
	{ "version",         0, NULL, 'v' },
};

/* Description of short options for getopt_long. */

static const char* const short_options = "a:hm:p:v";
/* Usage summary text. */

static const char* const usage_template =
"Usage: %s [ options ]\n"
"-u, --username USERNAME    Specify a username.\n"
"-p, --password PASSWORD    Specify password.\n"
"-h, --help                 Print this information.\n"
"-v, --version              Print version information.\n"


/* Print usage information and exit. If IS_ERROR is nonzero, write to
	stderr and use an error exit code. Otherwise, write to stdout and
	use a non-error termination code. Does not return. */

static void print_usage (int is_error)
{
	fprintf (is_error ? stderr : stdout, usage_template, program_name);
	exit (is_error ? 1 : 0);
}

int main (int argc, char* const argv[])
{

	int next_option;

	/* Store the program name, which we’ll use in error messages.*/
	program_name = argv[0];
	
	/*Default password*/
	password = 'test';
	/* Don’t print verbose messages. */
	verbose = 0;

	/* Parse options. */
	do {
		next_option =
			getopt_long (argc, argv, short_options, long_options, NULL);
		switch (next_option) {
		case 'u':
		/* User specified -u or --username. */
		{
			//
		}
		break;

		case 'p':
		/* User specified -p or --password.*/
		{
			//
		}
		break;

		case 'h':
			/* User specified -h or --help.*/
			print_usage (0);
	
		case 'v':
		/* User specified -v or --version. */
			printf("Notepost version 0.1\n");
		break;

		case '?':
			/* User specified an unrecognized option.*/
			print_usage (1);

		case -1:
		/* Done with options.*/
		break;
				
		default:
			abort (); // close program
		}
	} while (next_option != -1);
		
		/* This program takes no additional arguments.
			user specified any. */
		if (optind != argc)
			print_usage (1);

		/* Start the program. */
		//

	return 0;
}