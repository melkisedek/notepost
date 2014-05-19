# Default C compiler options.
CFLAGS= -Wall -std=c11 -D_POSIX_C_SOURCE -g 

notepost:
	gcc $(CFLAGS) -c members.c -I./headers -o members.o
	gcc $(CFLAGS) -c user_operations.c -I./headers -o user_operations.o
	gcc $(CFLAGS) -lcrypt -c encrypt.c -I./headers -o encrypt.o	
	gcc $(CFLAGS) -c start.c -I./headers -o start.o 
	gcc $(CFLAGS) -c main.c -I./headers -o main.o
	gcc $(CFLAGS) -lcrypt encrypt.o members.o user_operations.o main.o start.o -I./headers -L. -o notepost

clean:
	rm *.o notepost
