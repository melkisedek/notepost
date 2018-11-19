#Makafile
# Default C compiler options.
CFLAGS= -std=c11 -O3 -D_POSIX_C_SOURCE -g -Wall #-Wextra -Weverything
COMPLR = clang
EXE = notepost
RM = rm
# Windows
ifeq ($(OS), Windows_NT)
	EXE = notepost
	COMPLR = C:\MinGW64\bin\gcc.exe
	RM = del
endif

notepost:
	$(COMPLR) $(CFLAGS) -c members.c -I./headers -o members.o
	$(COMPLR) $(CFLAGS) -c note_ops.c -I./headers -o note_ops.o
	$(COMPLR) $(CFLAGS) -c user_operations.c -I./headers -o user_operations.o
	$(COMPLR) $(CFLAGS) -c encrypt.c -I./headers -o encrypt.o
	$(COMPLR) $(CFLAGS) -c start.c -I./headers -o start.o
	$(COMPLR) $(CFLAGS) -c common.c -I./headers -o common.o
	$(COMPLR) $(CFLAGS) -c sha256.c -I./headers -o sha256.o
	$(COMPLR) $(CFLAGS) -c main.c -I./headers -o main.o
	$(COMPLR) $(CFLAGS) -I./headers encrypt.o common.o sha256.o note_ops.o members.o user_operations.o main.o start.o  -L. -o $(EXE)


clean:
	$(RM) *.o

clean_all:
	$(RM) *.o *.data note_temp.* $(EXE)
