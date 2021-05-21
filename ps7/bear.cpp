#include<bits/stdc++.h>
using namespace std;


#define V 105
#define E 1010
#define INF 0x3FFFFFFF
// the index of the first outgoing edge for each vertex, initialised to -1
long long start[V];
// if e is an outgoing edge from u, succ[e] is another one, or -1
// cap[e] is the capacity / weight of the e
// to[e] is the destination vertex of e
long long succ[E], cap[E], to[E];
long long path[E];
long long edge_counter = 0;
void add_edge(long long u, long long v, long long c) {
    // set the properties of the new edge
    cap[edge_counter] = c, to[edge_counter] = v;
    // insert this edge at the start of u’s linked list of edges
    succ[edge_counter] = start[u];
    start[u] = edge_counter;
    ++ edge_counter;
}

// edges are in pairs so we can easily go between residuals & originals
long long inv(long long e) { 
    return e ^ 1;
} 

long long augment(long long s, long long t) {
    // This is a BFS, shortest path means by edge count not capacity
    queue<long long> q;
    // path[v] = which edge we used from to reach v
    fill(path, path + V, -1);
    for(q.push(s), path[s] = -2; !q.empty(); q.pop() ) {
        long long u = q.front();
        for(long long e = start[u]; ~e; e = succ[e]) {
            // if we can use e and we haven ’t already visited v, do it
            if(cap[e]<= 0) 
                continue;
            long long v = to[e];
            if(path[v] == -1) {
                path[v] = e;
                q.push(v);
            }
        }
    }
    // cout << "path" << path[t] << "\n";
    if(path[t] == -1) return 0; // can ’t reach the sink
    long long res = INF;
    // walk over the path backwards to find the minimum edge
    for(long long e = path[t]; e != -2; e = path[to[inv(e)]])
        res = min(res, cap[e]);
    // do it again to subtract that from the capacities
    for(long long e = path[t]; e != -2; e = path[to[inv(e)]]) {
        cap[e] -= res;
        cap[inv(e)] += res;
    }
    return res;
}

long long u[E], v[E], c[E];
long long source, sink;
long long m,n,x;
long long check(double mid) {
    edge_counter = 0;
    fill(start, start + V, -1);
    fill(succ, succ + E, 0);
    fill(cap, cap + E, 0);
    fill(to, to + E, 0);

    for (int i = 1; i <= m; ++i) {
        add_edge(u[i],v[i],floor(c[i]/mid));
        add_edge(v[i],u[i],0);
    }
    long long ans = 0;
    for (int i = 0; i <= m ; ++i) {
        ans += augment(source,sink);
    }
    // cout << ans <<"\n";
    return ans >= x;
}

int main() {
    cin >> n >> m >> x;
    source = 1;
    sink = n;
    for (int i = 1; i<=m; ++i) {
        cin >> u[i] >> v[i] >> c[i];
    }
    double left = 0;
    double right = 1e9;
    for (int i = 0; i < 100; ++i) {
        double mid = (left + right)/2;
        if (check(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    // cout << left;
    cout << fixed << setprecision(8) << left*x << "\n";

    return 0;
}