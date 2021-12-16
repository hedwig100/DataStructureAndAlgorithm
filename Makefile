CXX = g++
CXXFLAGS = -std=gnu++14

SIMPLEX_TESTSRCS = $(wildcard src/simplex/*.cpp)
SIMPLEX_TESTOBJS = $(SIMPLEX_TESTSRCS:%.cpp=%.o)

simplex_test: $(SIMPLEX_TESTOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

clean: 
	rm test $(TESTOBJS)

.PHONY: clean 
