CC = g++
CCFLAGS = -std=gnu++14

TESTSRCS = $(wildcard src/*.cpp)
TESTOBJS = $(TESTSRCS:%.cpp=%.o)

test: $(TESTOBJS)
	$(CC) $(CCFLAGS) -o $@ $^ 

clean: 
	rm test $(TESTOBJS)

.PHONY: clean 
