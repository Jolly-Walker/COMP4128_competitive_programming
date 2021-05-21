struct edge {
    int u, v, w;
    edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

vector<int> dist(n);
vector<edge> edges;
// global relaxation : try to relax every edge in the graph
// Returns if any distance was updated .
bool relax() {
    bool relaxed = false;
    for (auto e = edges.begin(); e != edges.end(); ++e) {
        // we don ’t want to relax an edge from an unreachable vertex
        if (dist [e->u] != INF && dist [e->v]> dist [e->u] + e->w) {
            relaxed = true;
            dist [e->v] = dist [e->u] + e->w;
        }
    }
    return relaxed;
}

vector<int> find_dist_and_check_neg_cycle() {
    fill(dist.begin(), dist.end(), INF );
    dist [n -1] = 0;
    // |V| -1 global relaxations
    for (int i = 0; i< n - 1; i ++) {
        relax();
    }
    // If any edge can be relaxed further, there is a negative cycle
    for (auto e = edges.begin(); e != edges.end(); ++e) {
        if (dist [e->u] != INF && dist [e->v] > dist [e->u] + e->w) {
            return true;
        }
    }
    // Otherwise, no negative cycle, that condition is actually a iff
    return false;
}