//encrypt.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strcmp, strcpy
#include <sys/stat.h>//file operations
#include <fcntl.h> //file operations
#include <unistd.h> //read, open, and other POSIX functions 
#include "common.h"
#include "sha256.h" //encryption algorithms

extern struct account user;

char* hash_password()
{
	uint8_t hash[SHA256_BYTES];
	int i, j;
    for (i = 0; i < (sizeof(&user.password) / sizeof(&user.password[0])); i += 2) {
		sha256(&user.password[i], strlen(&user.password[i]), hash);
		printf("input = '%s'\ndigest: %s\nresult: ", &user.password[i], &user.password[i + 1]);
		for (j = 0; j < SHA256_BYTES; j++){
			printf("%x",hash[j]);
		}
		printf("\n\n----%s----", hash);
	}
    strcpy(user.hash, hash);
	return user.hash;
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
        
    return 1; // Return a success.
}
