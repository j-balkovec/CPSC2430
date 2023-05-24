CC = g++
CFLAGS = -Wall -Werror -std=c++11 -pedantic

lab5: lab5.o
	$(CC) $(CFLAGS) lab5.o -o prog

lab5.o: lab5.cpp
	$(CC) $(CFLAGS) -c lab5.cpp

clean:
	rm -f *.o lab5
