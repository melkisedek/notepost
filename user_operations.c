//user_operations.c
#include <stdio.h>
#include <stdlib.h> //exit function
#include <string.h>
#include <errno.h> // for errno
#include <sys/stat.h>//file operations
#include <fcntl.h> //file operations
#include <unistd.h> //read, open, and other POSIX functions 
#include "common.h"

extern struct account user; //use struct defined in start.c
extern struct notice note;
void error();
int get_user_data();
int write_new_user();
int get_user_data();
int get_login_data();
int register_new_user();
char* hash_password();
int authenticate_user();
void member_functions(); //go to members(registered users) only functions

int login_user(){

	printf("Type your username and password below to login\n");
	printf(" Please type your username\n>");
	fgets(user.username, 80, stdin);
	printf(" Please type your password\n>");
	fgets(user.password, 400, stdin);

	//verify is doesn't already exist, if not existing terminate
	user.operation = get_login_data;
	if(user.operation() == -1){
		printf("User doesn't exist: %s\n", user.username);
		sleep(1);
		return -1;
	}else{//user exists, hash password
		strcpy(user.password,hash_password(user.password));

		user.operation = authenticate_user;
		if (user.operation() == 1)
		{
			printf("Login successful\n");
			sleep(1);
			return 1;
		} else
			printf("Authentication failed\n");
			sleep(1);
	}

	return 0;
}

int write_new_user(){
	int file_discriptor;
// open for read/write, create if not exist, append to end of file, 
//only the current user[as in computer, not this program] has r/w permission
	file_discriptor = open(USERDATA, O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);
	if (file_discriptor == -1)
		error("Failed to open USERDATA file");
	write(file_discriptor, &user, sizeof(struct account));
	close(file_discriptor);
	return 0;
}

/* This function reads the user data for the current name
from the file. It returns -1 if it is unable to find user
data for the current username. */
int get_user_data() {
    int file_discriptor, read_bytes;
    struct account entry;

    file_discriptor = open(USERDATA, O_RDONLY);
    if(file_discriptor == -1) // Can't open the file, maybe it doesn't exist
	   return -1;
	// Read the first chunk
    read_bytes = read(file_discriptor, &entry, sizeof(struct account)); 
    // Loop until proper username is found.
    while((strcmp(entry.username, user.username) != 0) && read_bytes > 0) { 
	   read_bytes = read(file_discriptor, &entry, sizeof(struct account)); 
	   // Keep reading.
    }
    close(file_discriptor); // Close the userdata file.
    if(read_bytes < sizeof(struct account)) 
    //This means that the end of file was reached.
        return -1; // not found
    else 
        user = entry; //copy to new entry
    return 1; // Return a success.
}

int register_new_user(){

	printf("> Hi, to register you need a username and password\n");
	printf("  Please type a username\n>>");
	fgets(user.username, 80, stdin);
	printf("  Please type a password\n>>");
	fgets(user.password, 400, stdin);
	//verify is doesn't already exist, if not existing,
	user.operation = get_user_data;
	if(user.operation() == -1){//hash password and save user to file
		strcpy(user.password,hash_password(user.password));
		user.operation = write_new_user;
		user.operation();
	}else{
		printf("# Sorry, someone with that username already exists.\n");
		sleep(1);
		return -1;
	}

	printf("# Please don\'t forget your username and password.\n");
	sleep(1);
	return 1;
}
