# Default C compiler options.
CFLAGS= -g 

notepost:
	gcc $(CFLAGS) -c start.c -I./headers -o start.o 
	gcc $(CFLAGS) -c main.c -I./headers -o main.o
	gcc $(CFLAGS) main.o start.o -I./headers -L. -o notepost

clean:
	rm *.o notepost
