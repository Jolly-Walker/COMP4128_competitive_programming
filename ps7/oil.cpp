#include<bits/stdc++.h>
using namespace std;

#define V 1010
#define E 300010
#define INF 0x3FFFFFFF
// the index of the first outgoing edge for each vertex, initialised to -1
int start[V];
// if e is an outgoing edge from u, succ[e] is another one, or -1
// cap[e] is the capacity / weight of the e
// to[e] is the destination vertex of e
int succ[E], cap[E], to[E];
int path[E];
int edge_counter = 0;
void add_edge(int u, int v, int c) {
    // set the properties of the new edge
    cap[edge_counter] = c, to[edge_counter] = v;
    // insert this edge at the start of u’s linked list of edges
    succ[edge_counter] = start[u];
    start[u] = edge_counter;
    ++ edge_counter;
}

// edges are in pairs so we can easily go between residuals & originals
int inv(int e) { 
    return e ^ 1;
} 

int augment(int s, int t) {
    // This is a BFS, shortest path means by edge count not capacity
    queue<int> q;
    // path[v] = which edge we used from to reach v
    fill(path, path + V, -1);
    for(q.push(s), path[s] = -2; !q.empty(); q.pop() ) {
        int u = q.front();
        for(int e = start[u]; ~e; e = succ[e]) {
            // if we can use e and we haven ’t already visited v, do it
            if(cap[e]<= 0) 
                continue;
            int v = to[e];
            if(path[v] == -1) {
                path[v] = e;
                q.push(v);
            }
        }
    }
    if(path[t] == -1) return 0; // can ’t reach the sink
    int res = INF;
    // walk over the path backwards to find the minimum edge
    for(int e = path[t]; e != -2; e = path[to[inv(e)]])
        res = min(res, cap[e]);
    // do it again to subtract that from the capacities
    for(int e = path[t]; e != -2; e = path[to[inv(e)]]) {
        cap[e] -= res;
        cap[inv(e)] += res;
    }
    return res;
}

bool monster[505];
int main() {
    int cases;
    cin >> cases;
    while(cases) {
        int size;
        cin >> size;

        for (int i = 1; i <= size; ++i) {
            add_edge(0,i,1);
            add_edge(i,0,1);
            add_edge(i+size,2*size + 1, 1);
            add_edge(2*size+1, i+size, 0);
        }
        for (int i = 1; i <= size; ++i) {
            for (int j = 1; j <= size; ++j) {
                char c;
                cin >> c;
                if (c == '#') {
                    add_edge(i,j + size,1)
                    add_edge(j + size,i,0)
                }
            }
        }
        int ans;
        int total = 0;
        while(augment(0,2*size+1)) {
            total += ans;
        }
        --cases;
    }
}