#include <bits/stdc++.h>
using namespace std;

#define maxn 105
vector<int> my_graph[maxn];
int energy[maxn];
bool dist[maxn][maxn];
int curr_energy[maxn];
struct edge {
    int u, v;
    edge(int _u, int _v) : u(_u), v(_v) {}
};

vector<edge> edges;



bool bellman(int n) {
    // set everything to negative inf
    for (int i = 1; i <= n; i++) {
        curr_energy[i]=-2e8;
    }
    // start with 100 energy
    curr_energy[1]=100;
    for (int k = 0; k < n-1; k++) {
        for (vector<edge>::iterator e = edges.begin(); e != edges.end(); ++e) {
            int u = e->u;
            int v = e->v;
            if (curr_energy[v] < curr_energy[u] + energy[v] && curr_energy[u] + energy[v] > 0) {
                curr_energy[v] = curr_energy[u] + energy[v];
            }
        }
    }
    for(vector<edge>::iterator e = edges.begin(); e != edges.end(); ++e) {
        int u = e->u;
        int v = e->v;
        if (curr_energy[v] < curr_energy[u] + energy[v] && curr_energy[u] + energy[v] > 0) {
            if(dist[v][n]) {
                return true;
            }
        }
    }
    return curr_energy[n] > 0;
}

void floyd_warshall(int n) {
    for ( int u = 1; u <= n; ++u) for ( int v = 1; v <= n; ++v) {
        dist[u][v] = false;
    }
    // update the distances for every directed edge
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= my_graph[i].size(); ++j) {
            dist[i][my_graph[i][j-1]] = 1;
            //cout << "add\n";
        }
    }

    for ( int i = 1; i <= n; i ++) {
        for ( int u = 1; u <= n; u ++) {
            for ( int v = 1; v <= n; v ++) {
                // dist [u][ v] is the length of the shortest path from u to v using only 0 to i -1 as intermediate vertices
                // now that we ’re allowed to also use i , the only new path that could be shorter is u -> i -> v
                //cout << u << " " << v << " " << i << " \n";
                dist[u][v] = dist[u][v] || (dist[u][i] && dist[i][v]);
                //cout << u << " " << v << " " << i << " \n";
            }
        }
    }
}
int main() {
    int num_rooms;
    while(true) {
        cin >> num_rooms;
        if (num_rooms == -1) break;

        //clear graph
        for (int i = 1; i < maxn; ++i) {
            my_graph[i].clear();
            energy[i] = 0;
        }
        edges.clear();
        // read rooms
        for (int i = 1; i <= num_rooms; ++i) {
            int num_out;
            cin >> energy[i] >> num_out;
            for (int j = 1; j <= num_out; ++j) {
                int out_room;
                cin >> out_room;
                my_graph[i].push_back(out_room);
                edges.push_back(edge(i, out_room));
            }
        }
        floyd_warshall(num_rooms);
        if (dist[1][num_rooms]) {
            // reachable so now calculate if hero has energy to get there
            if (bellman(num_rooms)) {
                cout << "winnable\n";
            } else {
                cout << "hopeless\n";
            }
        } else {
            cout << "hopeless\n";
        }
    }
    return 0;
}