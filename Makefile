CC = g++-11
CCFLAGS = -std=gnu++11

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o) 

all: $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^

test: $(TESTOBJS)
	$(CC) $(CCFLAGS) -o $@ $^ 

clean: 
	rm all test $(OBJS)

.PHONY: clean 
