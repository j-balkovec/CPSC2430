CC = g++
CFLAGS = -Wall -Werror -std=c++11 -pedantic -O3
#-O3 -> performance

SRCS = run.cpp CovidDB.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)




