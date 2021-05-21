#include <bits/stdc++.h>
using namespace std;
#define maxn 100010
typedef long long LL;
typedef pair<LL, int> edge; //(distance, vertex )


vector<edge> g[maxn];
priority_queue<edge, vector<edge>,greater<edge>> pq;
edge train[maxn];
LL dist[maxn];
int num_paths[maxn];
bool seen[maxn];

void dikstras() {
        pq.push(edge(0,1));
        fill(dist, dist+maxn, 0x3FFFFFFF);
        dist[1] = 0;
        while (!pq.empty()) {
            edge cur = pq.top();
            pq.pop();
            int v = cur.second;

            if (seen[v]) {
                continue;
            }
            seen[v] = true;
            // relax all edges from v
            for(int i = 0; i < g[v].size(); i ++) {
                edge next = g[v][i];
                int u = next.second;
                LL weight = next.first;
                //cout << u << " " << weight << "\n";
                //cout << dist[u] << " " << dist[v] << "\n";
                if (dist[u] > dist[v] + weight) {
                    dist[u] = dist[v] + weight;
                    pq.push(edge(dist[u], u));
                    num_paths[u] = 1;
                } else if (dist[u] == dist[v] + weight) {
                    ++num_paths[u];
                }
            }
        }
        return;
}

// n is cities
// m is roads
// k is trains
int main() {
    int n,m,k;
    cin >> n >> m >> k;

    for (int i = 1; i <= m; ++i) {
        int u, v;
        LL w;
        cin >> u >> v >> w;
        g[u].push_back(edge(w,v));
        g[v].push_back(edge(w,u));
    }

    for (int i = 1; i <= k; ++i) {
        int city;
        LL w;
        cin >> city >> w;
        train[i] = edge(w,city);
        g[1].push_back(edge(w,city));
        g[city].push_back(edge(w,1));
    }

    dikstras();
    // for (int i = 1; i <= n; ++i) {
    //     //cout << seen[i] << "\n";
    //     cout << num_paths[i] << "\n";
    // }
    int count = 0;
    for (int i = 1; i <= k; ++i) {
        int s = train[i].second;
        LL y = train[i].first;
        if (dist[s] < y) {
            ++count;
        }
        if (dist[s] == y) {
            if (num_paths[s] > 1) {
                ++count;
                --num_paths[s];
            }
        }
    }
    cout << count << "\n";
    return 0;
}