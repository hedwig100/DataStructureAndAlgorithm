CXX = g++
CXXFLAGS = -std=gnu++14

SIMPLEX_TESTSRCS = $(wildcard src/simplex/*.cpp)
SIMPLEX_TESTOBJS = $(SIMPLEX_TESTSRCS:%.cpp=%.o)

MAXFLOW_TESTSRCS = $(wildcard src/maxflow/*.cpp) 
MAXFLOW_TESTOBJS = $(MAXFLOW_TESTSRCS:%.cpp=%.o) 

simplex_test: $(SIMPLEX_TESTOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

maxflow_test: $(MAXFLOW_TESTOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

clean: 
	rm test $(TESTOBJS)

.PHONY: clean 
