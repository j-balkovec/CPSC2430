CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++11 -Werror 

SRCS = ShelterBST.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

all: prog

prog: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o prog

ShelterBST.o: ShelterBST.h ShelterBST.cpp
	$(CXX) $(CXXFLAGS) -c ShelterBST.cpp

main.o: ShelterBST.h main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(OBJS) prog


