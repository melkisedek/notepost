#include <stdio.h>    //printf
#include <stdlib.h>   //mkstemp
#include <string.h>   //strlen
#include <ctype.h>    //tolower
#include <sys/stat.h> //file operations
#include <fcntl.h>    //file operations
#include <unistd.h>   //read, open, and other POSIX functions
#include <time.h>     //date
#include "common.h"
#include "sha256.h" //encryption algorithm

extern struct notice note;

int member_functions()
{
    char choice[80];
    int i; //iterator

    printf("Welcome %s", note.note_user);

    while (1)
    {
        printf("What would you like to do?\n");
        printf(" 1. Create a note\n");
        printf(" 2. Delete a note\n");
        printf(" 3. exit this menu\n");
        printf("Type an action(verb) or option number to make a choice\n>");
        fgets(choice, 80, stdin); //don't want buffer overflow
        int len = strlen(choice);

        for (i = 0; i < len; i++)
        {
            choice[i] = tolower(choice[i]);
        }

        if ((strcmp("create\n", choice) == 0) || choice[0] == '1')
        {
            note.operation = create_note;
            note.operation();
        }
        else if ((strcmp("delete\n", choice) == 0) || choice[0] == '2')
        {
            // note.operation = delete_note;
            // if (note.operation() == -1)
            // {
            // 	printf("Note note found\n");
            // }
            printf("Sorry, the delete feature has been deactivated due to a bug.\n");
        }
        else if ((strcmp("exit\n", choice) == 0) || choice[0] == '3')
        {
            break; //user wants to exit members menu
        }
    }
    return 0;
}

/*All user who get here are already authenticated, safe to write the note*/
int create_note()
{
    int file_discriptor, i;
    time_t the_time;
    time(&the_time);
    strcpy(note.date, ctime(&the_time));

    printf("Enter the topic of your note\n>");
    fgets(note.topic, 100, stdin);

    int len = strlen(note.topic);
    //small letters only
    for (i = 0; i < len; i++)
    {
        note.topic[i] = tolower(note.topic[i]);
    }
    printf("Type a short description of your topic\n>");
    fgets(note.description, 2048, stdin);
    // open for read/write, create if not exist, append to end of file,
    //only the current user[as in computer, not this program] has r/w permission
    file_discriptor = open(NOTEDATA, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (file_discriptor == -1)
        exit_with_error_msg("Failed to open NOTEDATA file");
    if (write(file_discriptor, &note, sizeof(struct notice)) == -1)
    {
        close(file_discriptor);
        exit_with_error_msg("faied to write notedata:");
    }

    close(file_discriptor);
    return 0;
}

int delete_note()
{
    int file_discriptor, tmp_discriptor, i, read_bytes;
    struct notice entry;
    char choice[100];
    int len; //length of string in choice[]
    /* L_tmpnam declared in the stdio.h file.
    L_tmpnam define length of the generated file name.*/
    char tmp_file[L_tmpnam + 1]; // Add +1 for the null character.
    tmpnam(tmp_file);            //random filename

    tmp_discriptor = open(tmp_file, 'w'); //creates temporary file
    if (tmp_discriptor == -1)
    {
        exit_with_error_msg("Temporary file creation failed");
    }

    printf("Note: You can only delete notes you created\n");
    printf("Enter the topic of the note\n>");
    fgets(choice, 100, stdin);
    //small letters only, turn input (i.e choice[]) to small letters
    len = strlen(choice);
    for (i = 0; i < len; i++)
    {
        choice[i] = tolower(choice[i]);
    }

    file_discriptor = open(NOTEDATA, O_RDONLY, S_IRUSR | S_IWUSR);
    if (file_discriptor == -1) // Can't open the file, maybe it doesn't exist
        exit_with_error_msg("Failed to open NOTEDATA file");
    // first chunk
    read_bytes = read(file_discriptor, &entry, sizeof(struct notice));
    if (read_bytes == -1)
        exit_with_error_msg("Failed to read notedata:");

    // Loop until  username is found.
    if ((strcmp(entry.topic, choice) != 0) && (strcmp(entry.note_user, note.note_user) != 0) && read_bytes > 0)
    {
        //write read bytes to temporary file
        if (write(tmp_discriptor, &entry, sizeof(struct notice)) != read_bytes)
            exit_with_error_msg("failed to write temporary file");
        // Keep reading.
        read_bytes = read(file_discriptor, &entry, sizeof(struct notice));
        if (read_bytes == -1)
            exit_with_error_msg("Failed to read notedata:");
    }

    close(file_discriptor); // Close the notedata file.
    close(tmp_discriptor);  //close temporary file
    if (read_bytes < sizeof(struct notice))
    {
        //This means that the end of file was reached.
        unlink(tmp_file); //remove temp
        printf("---------end of file---------\n");
        return -1; // not found
    }

    //change permissions on new note (temp file) file
    if (chmod(tmp_file, S_IRUSR | S_IWUSR))
        exit_with_error_msg("error:");
    remove(NOTEDATA);           //remove note file
    rename(tmp_file, NOTEDATA); // save temp as note file

    return 0;
}
