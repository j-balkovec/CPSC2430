CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wpedantic
OBJS = pet.o main.o
TARGET = prog

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

pet.o: pet.cpp pet.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cpp pet.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
