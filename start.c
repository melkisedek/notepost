#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct account{
	char username[80];
	char password[400];
	char email[100];
	struct account *next;
} account;

void get_user_info(){

	char username[80];
	char password[400];
	char email[100];

	printf(">> Hi, to register you need an email and password\n");
	printf(">> Please type your email\n>>");
	fgets(email, 80, stdin);
	printf(">> Please type a password\n>>");
	fgets(password, 400, stdin);
	sscanf(email, "%[^@]s",username);
	//verify is doesn't already exist
	printf(">> Here's your generated username. Please don\'t forget it.\n>>");	
	printf("%s\n", username);
}

int start_menu(){
	char choice[80];
	
	int i; //loop index

	printf("-- Wecome to NotePost! --\n");
	printf(">>>>>>>>>>>>><*_*><<<<<<<<<<<\n" );
	printf("What would you like to do?\n");
	printf("> 1. login\n");
	printf("> 2. register\n");
	printf("> 3. view notes\n");
	printf("> 4. find a note\n");
	printf("> 5. EXIT\n");
	printf("Type an action or an option\'s number to make a choice\n>");
	fgets(choice, 80, stdin); //don't want buffer overflow
	int len = strlen(choice);

	for(i = 0; i<len; i++){
  		choice[i] = tolower(choice[i]);
	}
	
	if((strcmp("login\n", choice) == 0) || choice[0] == '1'){
		printf("%s", choice);
	}else if((strcmp("register\n", choice) == 0) || choice[0] == '2'){
		get_user_info();
	}else if((strcmp("view\n", choice) == 0) || choice[0] == '3'){
		printf("%s", choice);
	}else if((strcmp("find\n", choice) == 0) || choice[0] == '4'){
		printf("%s", choice);
	}else if((strcmp("exit\n", choice) == 0) || choice[0] == '5'){
		printf("Good bye.");
		return 0;
	} else printf("I din\'t understand. Try again please\n");
		
}