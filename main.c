#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> // for errno
#include <sys/types.h>
#include <signal.h> //interupt signal and other signals
#include <getopt.h> //argument option parsing
#include <unistd.h> //read, open, and other POSIX functions
#include "common.h"

int start_menu();
char *program_name; /* Name of the running program*/

/* Description of long options for getopt_long. */
/*1 is for options that take an argument e.g. -u myusername*/
static const struct option long_options[] = {
    {"start", 0, NULL, 's'},
    // { "username",      1, NULL, 'u' },
    // { "password",      1, NULL, 'p' },
    {"help", 0, NULL, 'h'},
    {"version", 0, NULL, 'v'},
};

/* Description of short options for getopt_long.*/
/* : for option that expect arguments when specified*/
static const char *const short_options = "su:p:hv";

/* Usage summary text. */
static const char *const usage_template =
    "Usage: %s [ options ]\n"
    // "-u, --username USERNAME    Specify a username.\n"
    // "-p, --password PASSWORD    Specify password.\n"
    "-h, --help                 Print this information.\n"
    "-v, --version              Print version information.\n";

/* Print usage information and exit. If IS_ERROR is nonzero, write to
    stderr and use an error exit code. Otherwise, write to stdout and
    use a non-error termination code. Does not return. */
static void print_usage(int is_error)
{
    fprintf(is_error ? stderr : stdout, usage_template, program_name);
    exit(is_error ? 1 : 0);
}

int main(int argc, char *const argv[])
{
    int next_option;

    /* Store the program name, which we’ll use in error messages.*/
    program_name = argv[0];

    /* Parse options. */
    do
    {
        next_option = getopt_long(argc, argv, short_options, long_options, NULL);
        switch (next_option)
        {
        case 's':

        case 'h':
            print_usage(0); /* User specified -h or --help.*/
        case 'v':
            printf("NotePost version 0.1\n"); /*User specified -v or --version.*/
            exit(0);                          //close program

        case '?':
            print_usage(1); /* User specified an unrecognized option.*/
        case -1:            /* Done with options.*/
            break;

        default:
            while (1)
            {
                if (start_menu() == 0)
                    return 0; //user wants to exit program
            }
        }
    } while (next_option != -1);

    /* This program takes no additional arguments, user specified any. */
    if (optind != argc)
        print_usage(1);
    else
    {
        // no arguments supplied, start the program
        while (1)
        {
            if (start_menu() == 0)
                return 0; //user wants to exit program
        }
    }

    return 0;
}
