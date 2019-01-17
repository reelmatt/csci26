# includes error/warning checking when compiling
CC = gcc -Wall -Wextra


fl: fl.o process.o ws13.o helpers.o
	$(CC) fl.o process.o ws13.o helpers.o -o fl
fl.o: fl.c
	$(CC) -c fl.c
process.o: process.c
	$(CC) -c process.c
ws13.o: ws13.c
	$(CC) -c ws13.c
helpers.o: helpers.c
	$(CC) -c helpers.c
clean:
	rm *.o