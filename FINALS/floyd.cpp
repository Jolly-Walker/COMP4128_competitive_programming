#include <bits/stdc++.h>
using namespace std;

#define maxn 205

double prob[maxn][maxn];
struct edge {
    int v;
    double chance;
    edge(int _v, double _chance) : v(_v), chance(_chance) {}
};

vector<edge> my_graph[maxn];
void floyd_warshall(int n) {
    for ( int u = 1; u <= n; ++u) for ( int v = 1; v <= n; ++v) {
        prob[u][v] = 0;
    }
    // update the distances for every directed edge
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= my_graph[i].size(); ++j) {
            prob[i][my_graph[i][j-1].v] = 1 - my_graph[i][j-1].chance;
        }
    }

    for (int i = 1; i <= n; ++i) {
        prob[i][i] = 1;
    }
    for ( int i = 1; i <= n; i ++) {
        for ( int u = 1; u <= n; u ++) {
            for ( int v = 1; v <= n; v ++) {
                // dist [u][ v] is the length of the shortest path from u to v using only 0 to i -1 as intermediate vertices
                // now that we ’re allowed to also use i , the only new path that could be shorter is u -> i -> v
                //cout << u << " " << v << " " << i << " \n";
                prob[u][v] = max(prob[u][v], prob[u][i] * prob[i][v]);
                //cout << u << " " << v << " " << i << " \n";
            }
        }
    }
}
int main() {
    int num_computers, num_edges;

    cin >> num_computers >> num_edges;
    //clear graph
    for (int i = 1; i <= num_edges; ++i) {
        int a,b;
        double chance;
        cin >> a >> b >> chance;
        
        my_graph[a].push_back(edge(b,chance));
        my_graph[b].push_back(edge(a,chance));
    }
    floyd_warshall(num_computers);
    
    for(int i = 1; i <= num_computers; ++i) {
        for(int j = 1; j <= num_computers; ++j) {
            cout << prob[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}