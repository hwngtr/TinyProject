CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

SRC = Vector.cpp Matrix.cpp LinearSystem.cpp main.cpp
OBJ = $(SRC:.cpp=.o)

all: simple_demo

simple_demo: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) simple_demo 