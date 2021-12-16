#include <stdio.h>
#include <vector>
#include <queue> 

struct edge{
    int to; 
    int flow; 
    int cost; 
    int inv; 

    edge(); 
    edge(int to,int flow,int cost,int inv);
}; 

struct MaxFlow{
    int n; 
    int m;
    std::vector<std::vector<edge>> G; 

    MaxFlow(int n,int m); 
    void add_edge(int a,int b,int cost); // add a -> b edge with cost, a and b are 0-indexed
    bool can_reach(int source,int tank,std::vector<int> &before); 
    int calc_flow(int source,int tank,std::vector<int> &before); 
    int edmonds_karp(int source,int tank); 
}; 