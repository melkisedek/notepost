#include "sha256.h" //encryption algorithms

void exit_with_error_msg();
// account struct to store information about users
struct account{
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
