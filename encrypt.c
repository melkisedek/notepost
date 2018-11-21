#include <stdio.h>
#include <stdlib.h>
#include <string.h>   //strcmp, strcpy
#include <sys/stat.h> //file operations
#include <fcntl.h>    //file operations
#include <unistd.h>   //read, open, and other POSIX functions
#include "common.h"


char *hash_password(char *passwd)
{
    uint8_t hash[SHA256_BYTES] = {0};    // init hash buffer to nulls
    char hash_string[SHA256_BYTES] = {0};
    char hex[3] = {0};

    sha256(passwd, strlen(passwd), hash);
    for (int j = 0; j < SHA256_BYTES; j++)
    {
        sprintf(hex, "%x", hash[j]);
        strcat(hash_string, hex);
    }
    strcpy(user.hash, hash_string);
    return user.hash;
}

int authenticate_user()
{
    int file_discriptor, read_bytes;
    struct account file_entry;

    file_discriptor = open(USERDATA, O_RDONLY);
    if (file_discriptor == -1) // Can't open the file, maybe it doesn't exist
        return -1;
    // Read the first chunk
    read_bytes = read(file_discriptor, &file_entry, sizeof(struct account));
    // Loop until proper username is found.
    while ((strcmp(file_entry.username, username) != 0) && read_bytes > 0)
    {
        read_bytes = read(file_discriptor, &file_entry, sizeof(struct account));
        // Keep reading.
    }
    close(file_discriptor); // Close the userdata file.
    if (read_bytes < sizeof(struct account))
    {
        //This means that the end of file was reached.
        return -1; // not found
    }
    else
    {
        if ((strcmp(file_entry.password, password) == 0))
            return 1; // passed, Return a success.
    }
    return 0; //normal return
}

int user_exists()
{
    int file_discriptor, read_bytes;
    struct account file_entry;

    file_discriptor = open(USERDATA, O_RDONLY);
    if (file_discriptor == -1) // Can't open the file, maybe it doesn't exist
        return -1;
    // Read the first chunk
    read_bytes = read(file_discriptor, &file_entry, sizeof(struct account));
    // Loop until proper username is found.
    while ((strcmp(file_entry.username, username) != 0) && read_bytes > 0)
    {
        read_bytes = read(file_discriptor, &file_entry, sizeof(struct account));
        // Keep reading.
    }
    close(file_discriptor); // Close the userdata file.
    if (read_bytes < sizeof(struct account))
        //This means that the end of file was reached.
        return -1; // not found

    return 1; // Return a success.
}
