#include <sys/stat.h>//file operations
#include <fcntl.h> //file operations
#include <crypt.h> //encryption algorithms
#include <unistd.h> //read, open, and other POSIX functions
#include "common.h"

//void error();

extern struct account user; //user struct
extern struct notice note;

/* This function reads the notedata for the current name
from the file. It returns -1 if it is unable to find notedata for the current username. */
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
	   read_bytes = read(file_discriptor, &entry, sizeof(struct account)); // Keep reading.
    }
    close(file_discriptor); // Close the userdata file.
    if(read_bytes < sizeof(struct account)) //This means that the end of file was reached.
        return -1; // not found
    else 
        user = entry; //copy to new entry
    return 1; // Return a success.
}