#ifndef COMMON_H_
#define COMMON_H_

#include "sha256.h" //encryption algorithms

void exit_with_error_msg();
// account struct to store information about users
struct account
{
    char username[80];
    char password[400];
    char hash[SHA256_BYTES];
    int (*operation)(); //function pointer to user operation
};

struct notice
{
    char note_user[80];
    char date[80];
    char topic[100];
    char description[2048];
    int (*operation)();
};

#define USERDATA "userdata.data" //user data
#define NOTEDATA "notedata.data" //notes
/*This is going to be the main handle for use operations*/
struct account user; //user struct
struct notice note;

void exit_with_error_msg(const char *msg);

char *hash_password();
int authenticate_user();
int get_login_data();

int member_functions();
/*
These 2 functions should only be accessible to registered users
*/
int create_note();
int delete_note();

int view_all_notes();
int find_notes();

int get_user_data();
int write_new_user();
int get_user_data();
int get_login_data();
int register_new_user();

int login_user();
int write_new_user();

int start_menu();
#endif