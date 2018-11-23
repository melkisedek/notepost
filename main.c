#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <ctype.h> //tolower() function
#include <errno.h> // for errno
#include <sys/types.h>
#include <signal.h> //interupt signal and other signals
#include <getopt.h> //argument option parsing
#include <unistd.h> //read, open, and sother POSIX functions
#include "common.h"

char *program_name; /* Name of the running program*/

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

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int create_database()
{
    sqlite3 *db = NULL;
    char *zErrMsg = 0;
    int  rc;
    char *sql;

    /* Open database */
    rc = sqlite3_open("notepost.db", &db);
    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stdout, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sql = "CREATE TABLE accounts(" \
            "id INTEGER PRIMARY KEY AUTOINCREMENT," \
            "username TEXT NOT NULL UNIQUE," \
            "password TEXT NOT NULL);" \
          "CREATE TABLE notes(" \
            "id INTEGER PRIMARY KEY AUTOINCREMENT," \
            "account_id INTEGER NOT NULL," \
            "date TEXT NOT NULL," \
            "title TEXT NOT NULL," \
            "details TEXT NOT NULL," \
            "FOREIGN KEY(account_id) REFERENCES accounts(id));";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }

    sqlite3_close(db);
    return 0;
}

void insert_user(const char *username, const char *password){
    sqlite3 *db = NULL;
    sqlite3_open("notepost.db", &db);

    const char* sql_insert_ = "INSERT INTO accounts ( username, password) VALUES (?,?)";
    sqlite3_stmt* stmt_insert_ = NULL;

    int rc = sqlite3_prepare_v2(db, sql_insert_, -1, &stmt_insert_, NULL);
    if(rc != SQLITE_OK){
        fprintf(stderr, "error: Prepare stmt stmt_insert_ failed, %s\n", sqlite3_errmsg(db));
        exit(3);
    }

    rc = sqlite3_bind_text(stmt_insert_, 1, username, strlen(username), NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "error: Bind %s to %d failed, %s\n", username, rc, sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(4);
    }

    rc = sqlite3_bind_text(stmt_insert_, 2, password, strlen(password), NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "error: Bind %s to %d failed, %s\n", password, rc, sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(4);
    }

    rc = sqlite3_step(stmt_insert_);
    if(rc == SQLITE_DONE) {
        printf("INSERT completed\n\n");
    } else {
        fprintf(stderr, "insert statement didn't return DONE (%i): %s\n", rc, sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt_insert_);
    sqlite3_close(db);
}

int user_exist(char *username){
    sqlite3 *db = NULL;
    sqlite3_open("notepost.db", &db);
    const char* sql = "Select * from accounts where username = ?";
    sqlite3_stmt *selectstmt_ = NULL;

    int rc = sqlite3_prepare_v2(db, sql, -1, &selectstmt_, NULL);
    if(rc != SQLITE_OK){
        fprintf(stderr, "error: Prepare stmt selectstmt_ failed, %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(3);
    }

    rc = sqlite3_bind_text(selectstmt_, 1, username, strlen(username), NULL);
    if(rc == SQLITE_OK)
    {
       if (sqlite3_step(selectstmt_) == SQLITE_ROW)
       {
            printf("Record found");// record found
            sqlite3_close(db);
            return 1;
       }
       else
       {
            printf("Record NOT found");// no record found
            sqlite3_close(db);
            return 0;
       }
    }
    sqlite3_finalize(selectstmt_);
    sqlite3_close(db);
    return 0;
}

int register_new_user()
{
    printf(" Hi, to register you need a username and password\n");
    printf("Please type a username\n>>");
    strcpy(user.username, get_string());
    printf("Please type a password\n");
    strcpy(user.password, get_string());
    //verify is doesn't already exist, if not existing,
    if (!user_exist(user.username))
    { //hash password and save user to file
        printf(user.username,"\n");
        hash_password(user.password);
        printf(user.hash,"\n");
        printf(user.password,"\n");
        insert_user(user.username, user.hash);
    }
    else
    {
        printf("# Sorry, someone with that username already exists.\n");
        return -1;
    }
    printf("# Please don\'t forget your username and password.\n");

    return 1;
}

int main(int argc, char *const argv[])
{
    int next_option;
    /* Store the program name, which we’ll use in error messages.*/
    program_name = argv[0];

    create_database();

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
