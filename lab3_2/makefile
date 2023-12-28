CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lUnitTest++

all: test_program

TableTranspositionCipher.o: TableTranspositionCipher.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test_main.o: test_main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test_program: TableTranspositionCipher.o test_main.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o test_program
