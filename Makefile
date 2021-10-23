CXX = g++
CXXFLAGS = -std=gnu++14

TESTSRCS = $(wildcard src/*.cpp)
TESTOBJS = $(TESTSRCS:%.cpp=%.o)

test: $(TESTOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

clean: 
	rm test $(TESTOBJS)

.PHONY: clean 
