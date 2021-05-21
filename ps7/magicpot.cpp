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
    edge_counter = 0;
    fill(start, start + V, -1);
    fill(succ, succ + E, 0);
    fill(cap, cap + E, 0);
    fill(to, to + E, 0);
    int num_hero, num_monster, num_pots;
    cin >> num_hero >> num_monster >> num_pots;
    int source = num_hero + num_monster + 1;
    int sink = num_hero + num_monster + 2;
    int potion = num_hero + num_monster + 3;
    add_edge(source, potion, num_pots);
    add_edge(potion, source, 0);
    for(int i = 0; i < num_hero; ++i) {
        int in_range;
        cin >> in_range;
        add_edge(source, i, 1);
        add_edge(i, source, 0);
        add_edge(potion, i, 1);
        add_edge(i, potion, 0);
        for (int j = 0; j < in_range; ++j) {
            int monster_num;
            cin >> monster_num;
            monster[monster_num] = true;
            add_edge(i, monster_num + num_hero, 1);
            add_edge(monster_num + num_hero, i, 0);
        }
    }

    for (int i = 1; i <= num_monster; ++i) {
        if (monster[i]) {
            add_edge(i + num_hero, sink, 1);
            add_edge(sink, i + num_hero, 0);
        }
    }
    int ans = 0;
    for (int i = 0; i < num_monster; ++ i) {
            ans += augment(source, sink);
            //cout << ans << "\n";
    }
    cout << ans << "\n";
    return 0;
}