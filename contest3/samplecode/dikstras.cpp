#include <queue>

typedef pair<int, int> edge; //(distance, vertex )
priority_queue<edge, vector<edge>,greater<edge>> pq;
// put the source s in the queue
pq.push(edge(0, s));
while (!pq.empty()) {
    // choose(d,v) so that d is minimal, 
    // i.e.the closest unvisited vertex
    edge cur = pq.top();
    pq.pop();
    int v = cur.second, d = cur.first;
    if (seen[v]) {
        continue;
    }

    dist[v] = d;
    seen[v] = true;
    // relax all edges from v
    for( int i = 0; i < edges[v].size(); i ++) {
        edge next = edges[v][i];
        int u = next.second, weight = next.first;
        if(!seen[u]) {
            pq.push(edge(d + weight, u));
        }
    }
}