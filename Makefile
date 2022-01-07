CXX = g++
CXXFLAGS = -std=gnu++14

C = gcc 
CFLAGS = -std=c11 -g

SIMPLEX_TESTSRCS = $(wildcard src/simplex/*.cpp)
SIMPLEX_TESTOBJS = $(SIMPLEX_TESTSRCS:%.cpp=%.o)

MAXFLOW_TESTSRCS = $(wildcard src/maxflow/*.cpp) 
MAXFLOW_TESTOBJS = $(MAXFLOW_TESTSRCS:%.cpp=%.o) 

RBTREE_TESTSRCS = $(wildcard src/red_black_tree/*.cpp) 
RBTREE_TESTOBJS = $(RBTREE_TESTSRCS:%.cpp=%.o) 

HASH_TESTSRCS = $(wildcard src/hash/*.c) 
HASH_TESTOBJS = $(HASH_TESTSRCS:%.c=%.o) 

simplex_test: $(SIMPLEX_TESTOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

maxflow_test: $(MAXFLOW_TESTOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

rbtree_test: $(RBTREE_TESTOBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

hash_test: $(HASH_TESTOBJS)
	$(C) $(CFLAGS) -o $@ $^ 

clean: 
	rm test $(TESTOBJS)

.PHONY: clean 
