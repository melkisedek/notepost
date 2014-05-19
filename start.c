#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //tolower() function
#include "common.h"

//display error and exit
void error();
int login_user();
int write_new_user();
int get_user_data();
int register_new_user();
int member_functions(); //go to members(registered users) only functions
int authenticate_user(); // make sure user exists

extern struct account user;

int start_menu(){
	char choice[80];
	
	int i; //loop index

	printf("---- Wecome to NotePost! ----\n");
	printf("------------(^_^)------------\n" );
	printf("  1. login\n");
	printf("  2. register\n");
	printf("  3. view notes\n");
	printf("  4. find a note\n");
	printf("  5. create or delete a note\n");
	printf("  6. exit \n");
	printf("Type an action(verb) or option number to make a choice\n>");
	fgets(choice, 80, stdin); //don't want buffer overflow
	int len = strlen(choice);

	for(i = 0; i<len; i++){
  		choice[i] = tolower(choice[i]);
	}
	
	if((strcmp("login\n", choice) == 0) || choice[0] == '1'){
		user.operation = login_user;
		user.operation();
	}
	else if((strcmp("register\n", choice) == 0) || choice[0] == '2'){
		user.operation = register_new_user;
		user.operation();
	}
	else if((strcmp("view\n", choice) == 0) || choice[0] == '3'){
		printf("%s", choice);
	}
	else if((strcmp("find\n", choice) == 0) || choice[0] == '4'){
		printf("%s", choice);
	}
	else if((strcmp("create\n", choice) == 0) || 
		(strcmp("delete\n", choice) == 0) ||choice[0] == '5'){
			user.operation = authenticate_user;
			if (user.operation() == 1){
				printf("Login successful\n");
				strcpy(note.note_user,user.username); // make logged in user a note user
				note.operation = member_functions;
				
				while(1){
					if(note.operation() == 0)
						break;//user wants to exit members menu
					}
			} else
				printf("Authentication failed\n");
	}
	else if((strcmp("exit\n", choice) == 0) || choice[0] == '6'){
		printf("Good bye :-)\n");
		return 0; //return 0 to main for termination
	}
	else printf("# I din\'t understand. Try again please\n");
		
	return 1;
}