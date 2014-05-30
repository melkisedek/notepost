//encrypt.c
#include <stdio.h>
#include <string.h> //strcmp, strcpy
#include <sys/stat.h>//file operations
#include <fcntl.h> //file operations
#include <crypt.h> //encryption algorithms
#include <unistd.h> //read, open, and other POSIX functions 
#include "common.h"

extern struct account user;
void error();

char* hash_password()
{
	//keep the seed the same so that 
	//hashes are the same for the same words
	unsigned long seed[2]={9989987,9978788};
 	char salt[] = "$6$"; //SHA-512 encryption, 86 characters
 	const char *const seedchars =
   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
   "abcdefghijklmnopqrstuvwxyz./0123456789";
   int i;
   /* Turn it into printable characters from `seedchars'. */
	 for (i = 0; i < 8; i++)
	   salt[3+i] = seedchars[(seed[i/5] >> (i%5)*6) & 0x3f];
    char *encrypted;
    encrypted = crypt(user.password, salt);
    if (encrypted == NULL)
	     error("Hash failed");
	strcat(encrypted,"\n"); //terminate like fgets '\n\0'
	return encrypted;
}

int authenticate_user() {
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
    if(read_bytes < sizeof(struct account)) {
    //This means that the end of file was reached.
        return -1; // not found
    }
    else {
       	if ((strcmp(entry.password, user.password) == 0))
	 		return 1;// passed, Return a success.
	 }
	return 0; //normal return
}

int get_login_data() {
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
        ; //user found, do nothing
    return 1; // Return a success.
}
