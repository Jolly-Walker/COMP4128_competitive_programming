#include<bits/stdc++.h>
using namespace std;

#define V 205
#define E 100010
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

int main() {

    int num_nodes;
    while (cin >> num_nodes) {
        edge_counter = 0;
        fill(start, start + V, -1);
        fill(succ, succ + E, 0);
        fill(cap, cap + E, 0);
        fill(to, to + E, 0);
        for (int i = 1; i <= num_nodes; ++i) {
            int node_cap;
            cin >> node_cap;
            add_edge(2*i, 2*i+1, node_cap);
            add_edge(2*i+1, 2*i, 0);
        }
        int num_edges, u, j, c;
        cin >> num_edges;
        for (int i = 0; i < num_edges; ++i) {
            cin >> u >> j >> c;
            add_edge(2*u+1,2*j,c);
            add_edge(2*j,2*u+1,0);
        }
        int b, d;
        cin >> b >> d;
        for (int i = 0; i < b; ++i) {
            int tmp;
            cin >> tmp;
            add_edge(0,2*tmp, INF);
            add_edge(2*tmp, 0, 0);
        }
        for (int i = 0; i < d; ++i) {
            int tmp;
            cin >> tmp;
            add_edge(1, 2*tmp+1, 0);
            add_edge(2*tmp+1, 1, INF);
        }
        int ans = 0;
        for (int i = 0; i < num_nodes - 1; ++ i) {
            ans += augment(0, 1);
        }
        cout << ans << "\n";
    }
    return 0;
}