#ifndef MAIN_H
#define MAIN_H

//display error and terminate
void error(const char* msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

/*This function runs when someone presses CRL-C*/
void handle_shutdown(int sig){
	fprintf(stderr, "\nGood Bye!\n");
	exit(0);
}

#endif