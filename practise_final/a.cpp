#include <iostream>
#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

// the index of the first outgoing edge for each vertex, initialised to -1
int start[2005];
// if e is an outgoing edge from u, succ[e] is another one, or -1
// cap[e] is the capacity/weight of the e
// to[e] is the destination vertex of e
int succ[8000], cap[8000], to[8000];

int edge_counter = 0;
void add_edge(int u, int v, int c) {
  // set the properties of the new edge
  cap[edge_counter] = c, to[edge_counter] = v;
  // insert this edge at the start of u's linked list of edges
  succ[edge_counter] = start[u];
  start[u] = edge_counter;
  ++edge_counter;
}

int seen[2005];
int path[2005];

int inv(int e) { return e ^ 1; }

int augment(int s, int t) {
  // This is a BFS, shortest path means by edge count not capacity
  queue<int> q;
  // path[v] = which edge we used from to reach v
  fill(path, path + 2005, -1);
  for (q.push(s), path[s] = -2; !q.empty(); q.pop()) {
    int u = q.front();
    for (int e = start[u]; ~e; e = succ[e]) {
      // if we can use e and we haven't already visited v, do it
      if (cap[e] <= 0) continue;
      int v = to[e];
      if (path[v] == -1) {
        path[v] = e;
        q.push(v);
      }
    }
  }
  if (path[t] == -1) return 0; // can't reach the sink
  int res = 1e9;
  // walk over the path backwards to find the minimum edge
  for (int e = path[t]; e != -2; e = path[to[inv(e)]])
    res = min(res, cap[e]);
  // do it again to subtract that from the capacities
  for (int e = path[t]; e != -2; e = path[to[inv(e)]]) {
    cap[e] -= res;
    cap[inv(e)] += res;
  }
  return res;
}

int max_flow(int s, int t) {
  int res = 0;
  fill(seen, seen + 2005, 0);
  while (augment(s, t)) {
    fill(seen, seen + 2005, 0);
    res += 1;
  }
  return res;
}

int main() {
    fill(start, start + 2005, -1);
    int n, p;
    cin >> n >> p;
    assert(n >= 1 && n <= 1000 && "n out of bounds");
    assert(p >= 1 && p <= 1000 && "p out of bounds");
    for (int i = 1; i <= n; ++i) {
        int c; cin >> c;
        assert(c >= 0 && c <= p && "cap out of bounds");
        add_edge(0, i, c);
        add_edge(i, 0, 0);
    }
    for (int i = 1; i <= p; ++i) {
        int c; cin >> c;
        assert(c >= 0 && c <= n && "cap out of bounds");
        add_edge(i + 1000, 2003, c);
        add_edge(2003, i + 1000, 0);
    }
    for (int i = 1; i <= n; ++i) {
        int k, v;
        cin >> k;
        while (k --> 0) {
            cin >> v;
            assert(v >= 1 && v <= p && "v out of bounds");
            add_edge(i, 1000 + v, 1);
            add_edge(1000 + v, i, 0);
        }
    }
    char x;
    cin >> x;
    assert(cin.eof());
    cout << max_flow(0, 2003) << '\n';
    return 0;
}

