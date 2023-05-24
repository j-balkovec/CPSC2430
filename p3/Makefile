CC=g++
CFLAGS= -g -Wall -Werror -pedantic -std=c++11

SRCS=ShelterBST.cpp assignment3.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: prog

prog: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o prog

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) prog
