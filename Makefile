#Makafile
# Default C compiler options.
CFLAGS= -std=c11 -O3 -D_POSIX_C_SOURCE -g -pedantic -Wall -Wextra -Weverything
COMPLR = clang
notepost:
	#$(COMPLR) $(CFLAGS) common.c members.c note_ops.c user_operations.c encrypt.c start.c main.c -I./headers -o notepost
	$(COMPLR) $(CFLAGS) -c members.c -I./headers -o members.o
	$(COMPLR) $(CFLAGS) -c note_ops.c -I./headers -o note_ops.o
	$(COMPLR) $(CFLAGS) -c user_operations.c -I./headers -o user_operations.o
	$(COMPLR) $(CFLAGS) -lcrypt -c encrypt.c -I./headers -o encrypt.o
	$(COMPLR) $(CFLAGS) -c start.c -I./headers -o start.o
	$(COMPLR) $(CFLAGS) -c common.c -I./headers -o common.o
	$(COMPLR) $(CFLAGS) -c sha256.c -I./headers -o sha256.o
	$(COMPLR) $(CFLAGS) -c main.c -I./headers -o main.o
	$(COMPLR) $(CFLAGS)  encrypt.o common.o sha256.c note_ops.o members.o user_operations.o main.o start.o -I./headers -L. -o notepost


clean:
	rm *.o notepost

clean_all:
	rm *.o *.data note_temp.* notepost
