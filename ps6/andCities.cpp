#include <bits/stdc++.h>
using namespace std;
#define maxn 100010
typedef long long LL;
typedef pair<int, int> edge; //(distance, vertex )


vector<edge> g[maxn];
priority_queue<edge, vector<edge>,greater<edge>> pq;
edge train[maxn];
int dist[maxn];
bool seen[maxn];

void dikstras() {
        pq.push(edge(0,1));
        fill(dist, dist+maxn, 0x3FFFFFFF);
        dist[1] = 0;
        while (!pq.empty()) {
            edge cur = pq.top();
            pq.pop();
            int v = cur.second;
            int d = cur.first;

            if (seen[v]) {
                continue;
            }
            seen[v] = true;
            // relax all edges from v
            for( int i = 0; i < g[v].size(); i ++) {
                edge next = g[v][i];
                int u = next.second;
                int weight = next.first;
                //cout << u << " " << weight << "\n";
                //cout << dist[u] << " " << dist[v] << "\n";
                if (dist[u] > dist[v] + weight) {
                    dist[u] = dist[v] + weight;
                    pq.push(edge(d + weight, u));
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
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back(edge(w,v));
        g[v].push_back(edge(w,u));
    }

    for (int i = 1; i <= k; ++i) {
        int city;
        int w;
        cin >> city >> w;
        train[i] = edge(w,city);
    }

    dikstras();
    for (int i = 1; i <= n; ++i) {
        //cout << seen[i] << "\n";
    }

    for(int i = 1 ; i <= n ; ++i) {
        for(int j = 0 ; j < g[i].size();j++) {
            if(dis[i] + ver[i][j].second == dis[ver[i][j].first])
				In[ver[i][j].first]++;
        }
    }
    int count = 0;
    for (int i = 1; i <= k; ++i) {
        int s = train[i].second;
        int y = train[i].first;
        if (dist[s] <= y) {
            ++count;
        }
    }
    cout << count << "\n";
    return 0;
}