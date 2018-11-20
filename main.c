#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //tolower() function
#include <errno.h> // for errno
#include <sys/types.h>
#include <signal.h> //interupt signal and other signals
#include <getopt.h> //argument option parsing
#include <unistd.h> //read, open, and other POSIX functions
#include "common.h"

int start_menu();
char *program_name; /* Name of the running program*/
extern struct account user;

int start_menu()
{
    char choice[80];
    int i; //loop index

    printf("---- Wecome to NotePost! ----\n");
    printf("------------(^_^)------------\n");
    printf("  1. login\n");
    printf("  2. register\n");
    printf("  3. view notes\n");
    printf("  4. find a note\n");
    printf("  5. create or delete a note\n");
    printf("  6. exit \n");
    printf("Type an action(verb) or option number to make a choice\n>");
    fgets(choice, 80, stdin); //don't want buffer overflow
    int len = strlen(choice);

    for (i = 0; i < len; i++)
    {
        choice[i] = tolower(choice[i]);
    }

    if ((strcmp("login\n", choice) == 0) || choice[0] == '1')
    {
        user.operation = login_user;
        user.operation();
    }
    else if ((strcmp("register\n", choice) == 0) || choice[0] == '2')
    {
        user.operation = register_new_user;
        user.operation();
    }
    else if ((strcmp("view\n", choice) == 0) || choice[0] == '3')
    {
        view_all_notes();
    }
    else if ((strcmp("find\n", choice) == 0) || choice[0] == '4')
    {
        find_notes();
        //printf("Functin disable due to bug\n");
    }
    else if ((strcmp("create\n", choice) == 0) ||
             (strcmp("delete\n", choice) == 0) || choice[0] == '5')
    {
        user.operation = authenticate_user;
        if (user.operation() == 1)
        {
            strcpy(note.note_user, user.username);
            // make logged in user a note user
            note.operation = member_functions;

            while (1)
            {
                if (note.operation() == 0)
                    break; //user wants to exit members menu
            }
        }
        else
        {
            printf("Authentication failed. Login first.\n");
            sleep(1);
        }
    }
    else if ((strcmp("exit\n", choice) == 0) || choice[0] == '6')
    {
        printf("Good bye :-)\n");
        return 0; //return 0 to main for termination
    }
    else
    {
        printf("# I din\'t understand. Try again please\n");
        sleep(1);
    }
    return 1;
}

/* Description of long options for getopt_long. */
/*1 is for options that take an argument e.g. -u myusername*/
static const struct option long_options[] = {
    { "username",      1, NULL, 'u' },
    { "password",      1, NULL, 'p' },
    {"help", 0, NULL, 'h'},
    {"version", 0, NULL, 'v'},
};

/* Description of short options for getopt_long.*/
/* : for option that expect arguments when specified*/
static const char *const short_options = "u:p:hv";

/* Usage summary text. */
static const char *const usage_template =
    "Usage: %s [ options ]\n"
    "-u, --username USERNAME    Specify a username.\n"
    "-p, --password PASSWORD    Specify password.\n"
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
            while (1)
            {
                if (start_menu() == 0)
                    return 0; //user wants to exit program
            }
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
            abort(); // close program
        }
    } while (next_option != -1);

    //user typed no arguments, print help info
    printf("%s: arguments missing \n", program_name);
    printf("Try \'%s --help\' for more information.' \n", program_name);
    /* This program takes no additional arguments, user specified any. */
    if (optind != argc)
        print_usage(1);

    return 0;
}
