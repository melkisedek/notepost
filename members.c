#include <stdio.h> //printf
#include <string.h> //strlen
#include <ctype.h> //tolower
#include <sys/stat.h>//file operations
#include <fcntl.h> //file operations
#include <crypt.h> //encryption algorithms
#include <unistd.h> //read, open, and other POSIX functions
#include <time.h>
#include "common.h"

extern struct notice note;
/*
These functions should only be accessible to registered users
*/
void error(); //display error and exit
int create_note();
int delete_note();

int member_functions(){
	char choice[80];
	int i; //iterator

	printf("Welcome %s\n", note.note_user);

	while(1){
		printf("What would you like to do?\n");
		printf(" 1. Create a note\n");
		printf(" 2. Delete a note\n");
		printf(" 3. exit this menu\n");
		printf("Type an action(verb) or option number to make a choice\n>");
		fgets(choice, 80, stdin); //don't want buffer overflow
		int len = strlen(choice);

		for(i = 0; i<len; i++){
	  		choice[i] = tolower(choice[i]);
		} 

		if ((strcmp("create\n", choice) == 0)||choice[0] == '1'){
			note.operation = create_note;
			note.operation();
		}
		else if ((strcmp("delete\n", choice) == 0)||choice[0] == '2'){
			/* code */
		}
		else if ((strcmp("exit\n", choice) == 0) || choice[0] == '3'){
			break;//user wants to exit members menu
		}
	}
	return 0;
}

/*All user who get here are already authenticated, safe to write the note*/

int create_note(){
	int file_discriptor;
	long int seconds;
	const time_t *the_time;
	seconds = time(NULL);
	the_time = &seconds;
	strcpy(note.date, ctime(the_time));
	note.time_seconds = seconds;
		printf("Enter the topic of your note\n>");
		fgets(note.topic, 100, stdin);
		printf("Type a short description of your topic\n>");
		fgets(note.description, 2048, stdin);
// open for read/write, create if not exist, append to end of file, 
//only the current user[as in computer, not this program] has r/w permission
	file_discriptor = open(NOTEDATA, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
	if (file_discriptor == -1)
		error("Failed to open NOTEDATA file");
	write(file_discriptor, &note, sizeof(struct notice));
	close(file_discriptor);
	return 0;
}