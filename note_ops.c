#include <stdio.h>
#include <string.h> //strerror()
#include <ctype.h> //tolower()
#include <errno.h> //errno variable
#include <sys/stat.h>//file operations
#include <fcntl.h> //file operations
#include <crypt.h> //encryption algorithms
#include <unistd.h> //read, open, and other POSIX functions
#include "common.h"

//void error();

extern struct account user; //user struct
extern struct notice note;

/* This function reads the notedata from the file. 
It returns -1 if it is unable to find notedata.*/
int view_all_notes() {
    int file_discriptor, read_bytes;
    struct notice entry;

    file_discriptor = open(NOTEDATA, O_RDONLY);
    if(file_discriptor == -1){ // Can't open the file, maybe it doesn't exist
	   printf("Error: Couldn't open notedata file: %s\n",strerror(errno));
       return -1;
    }
	// Read the first chunk
    read_bytes = read(file_discriptor, &entry, sizeof(struct notice)); 
    // Loop until file ends
    while(read_bytes > 0) { 
        // print out and Keep reading.
        printf(" Uploader: %s Date: %s Topic: %s Description: %s", 
            entry.note_user, entry.date, entry.topic, entry.description);
        printf("--------------------------------------------------\n");
	   read_bytes = read(file_discriptor, &entry, sizeof(struct notice)); 
    }
    close(file_discriptor); // Close the userdata file.
    if(read_bytes < sizeof(struct notice)){ //This means that the end of file was reached.
        printf("---------end of file---------\n");
        return -1; // not found
    }

    return 1; // Return a success.
}

int find_notes() {
    int file_discriptor, read_bytes, i;
    struct notice entry;
    char choice[100];

    printf("Enter the search topic\n>");
    fgets(choice, 100, stdin);

    int len = strlen(choice);
    //small letters only
    for(i = 0; i<len; i++){
        choice[i] = tolower(choice[i]);
    }

    file_discriptor = open(NOTEDATA, O_RDONLY);
    if(file_discriptor == -1){ // Can't open the file, maybe it doesn't exist
       printf("Error: Couldn't open notedata file: %s\n",strerror(errno));
       return -1;
    }
    // Read the first chunk
    read_bytes = read(file_discriptor, &entry, sizeof(struct notice)); 
    // Loop until file ends
    while(read_bytes > 0) { 
        if (strcmp(entry.topic, choice) == 0){
            // print out and Keep reading.
            printf(" Uploader: %s Date: %s Topic: %s Description: %s", 
                entry.note_user, entry.date, entry.topic, entry.description);
            printf("--------------------------------------------------\n");
           read_bytes = read(file_discriptor, &entry, sizeof(struct notice));
        }
    }
    close(file_discriptor); // Close the userdata file.
    if(read_bytes < sizeof(struct notice)){ //This means that the end of file was reached.
        printf("---------end of file---------\n");
        return -1; // not found
    }

    return 1; // Return a success.
}