#Makafile
# Default C compiler options.
CFLAGS= -Wall -std=c11 -D_POSIX_C_SOURCE -g 

notepost:
	gcc $(CFLAGS) -c members.c note_ops.c user_operations.c encrypt.c start.c main.c -I./headers -o notepost

clean:
	rm *.o notepost

clean_all:
	rm *.o *.data note_temp.* notepost
