#include <stdio.h> 
#include <cassert> 
#include "maxflow.hpp" 

void test1() {
    int n = 4; 
    int m = 5; 
    MaxFlow mf(n,m); 
    mf.add_edge(0,1,2); 
    mf.add_edge(0,2,1); 
    mf.add_edge(1,2,1); 
    mf.add_edge(1,3,1); 
    mf.add_edge(2,3,2); 
    int ans = mf.edmonds_karp(0,n-1); 
    printf("ans: %d\n",ans); 
    assert(ans == 3); 
}

int main() {
    test1();
    return 0;
}