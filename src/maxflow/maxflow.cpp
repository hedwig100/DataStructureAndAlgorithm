#include "maxflow.hpp"

const int MAX_FLOW = 100'000'000;

edge::edge(int to,int flow,int cost,int inv): to(to),flow(flow),cost(cost),inv(inv) {}

MaxFlow::MaxFlow(int n,int m):n(n),m(m) {
    G.resize(n); 
}

void MaxFlow::add_edge(int a,int b,int cost) {
    int a_length = (int)G[a].size(); 
    int b_length = (int)G[b].size(); 
    // G[a].push_back(edge(b,   0,cost,b_length)); 
    // G[b].push_back(edge(a,cost,cost,a_length));
    G[a].emplace_back(b,   0,cost,b_length); 
    G[b].emplace_back(a,cost,cost,a_length);
}

bool MaxFlow::can_reach(int source,int tank,std::vector<int> &before) {
    std::queue<int> q; 
    q.push(source); 
    before[source] = 0; 

    while (!q.empty()) {
        int v = q.front(); q.pop(); 
        for (edge &e : G[v]) {
            if (before[e.to] < 0 && e.cost - e.flow > 0) {
                q.push(e.to); 
                before[e.to] = v; 
            }
        }
    }

    return (before[tank] >= 0); 
}

int MaxFlow::calc_flow(int source,int tank,std::vector<int> &before) {

    // calc augmenting flow 
    int can_flow = MAX_FLOW; 
    int v = tank; 
    while (v != source) {
        int u = before[v]; 
        for (edge &e : G[u]) {
            if (e.to == v) {
                can_flow = std::min(can_flow,e.cost - e.flow); 
                break; 
            }
        }
        v = u; 
    }

    // recreate residual graph 
    v = tank; 
    while (v != source) {
        int u = before[v]; 
        for (edge &e : G[u]) {
            if (e.to == v) {
                e.flow += can_flow; 
                G[v][e.inv].flow -= can_flow;
                break;
            }
        }
        v = u; 
    }

    return can_flow; 
}

int MaxFlow::edmonds_karp(int source,int tank) {
    int maxflow = 0;
    std::vector<int> before(n,-1); 
    while (can_reach(source,tank,before)) {
        maxflow += calc_flow(source,tank,before);
        std::fill(before.begin(),before.end(),-1);
    }
    return maxflow; 
}

