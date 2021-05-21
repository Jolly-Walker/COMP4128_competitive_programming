#include <bits/stdc++.h>

using namespace std;
#define maxn 100010

vector<pair<int,int>> g[maxn];
bool gives[maxn][9];
bool requires[maxn][9];


typedef pair<int, int> edge; //(distance, vertex )

bool f_custom(pair<edge,vector<bool>> const & lhs, pair<edge,vector<bool>> const & rhs) {
    edge left = lhs.first;
    edge right = rhs.first;

    if (left.first == right.first) {
        return left.second > right.second;
    }
    return left.first > right.first;
}
priority_queue<pair<edge,vector<bool>>, vector<pair<edge,vector<bool>>>, function<bool(pair<edge,vector<bool>>&, pair<edge,vector<bool>>&)>> pq(f_custom);
bool seen[maxn][9];
int dist[maxn];
// put the source s in the queue
void dikstras(int n) {
    pq.push(make_pair(edge(0, 1),vector<bool>{false, false, false, false, false, false, false, false, false, false}));
    while (!pq.empty()) {
        // choose(d,v) so that d is minimal, 
        // i.e.the closest unvisited vertex
        pair<edge,vector<bool>> cur = pq.top();
        pq.pop();
        edge cur_edge = cur.first;
        int v = cur_edge.second, d = cur_edge.first;
        vector<bool> has_cert = cur.second;
        if (v == n) {
            cout << d << "\n";
            return;
        }
        
        if (has_cert[1]) {
            if (seen[v][1]) {
                continue;
            }
        } else if (has_cert[2]) {
            if (seen[v][2]) {
                continue;
            }
        }else if (has_cert[3]) {
            if (seen[v][3]) {
                continue;
            }
        } else if (has_cert[4]) {
            if (seen[v][4]) {
                continue;
            }
        } else if (has_cert[5]) {
            if (seen[v][5]) {
                continue;
            }
        } else if (has_cert[6]) {
            if (seen[v][6]) {
                continue;
            }
        } else if (has_cert[7]) {
            if (seen[v][7]) {
                continue;
            }
        } else if (has_cert[8]) {
            if (seen[v][8]) {
                continue;
            }
        } else {
            if (seen[v][0]) {
                continue;
            }
        }

        dist[v] = d;
        seen[v][0] = true;
        for (int i = 1; i <= 8; ++i) {
            if (has_cert[i]) {
                seen[v][i] = true;
            }
        }
        // relax all edges from v
        for( int i = 0; i < g[v].size(); i ++) {
            edge next = g[v][i];
            int u = next.second, weight = next.first;
            
            bool check1 = has_cert[1] || !requires[u][1];
            bool check2 = has_cert[2] || !requires[u][2];
            bool check3 = has_cert[3] || !requires[u][3];
            bool check4 = has_cert[4] || !requires[u][4];
            bool check5 = has_cert[5] || !requires[u][5];
            bool check6 = has_cert[6] || !requires[u][6];
            bool check7 = has_cert[7] || !requires[u][7];
            bool check8 = has_cert[8] || !requires[u][8];
            bool check = check1 && check2 && check3 && check4 && check5 && check6 && check7 && check8;
            //cout << "v is : " << v << " u is : " << u << " and check is: " << has_cert[1] << "\n";
            vector<bool> new_cert = vector<bool>(has_cert);
            for (int j = 1; j <= 8; ++j) {
                if (gives[u][j]) {
                    new_cert[j] = true;
                    //cout << "FUCKKK\n";
                }
            }
            //cout << "v is : " << v << " u is : " << u << " and new is: " << new_cert[1] << "\n";
            if(!seen[u][0] && check) {
                pq.push(make_pair(edge(d + weight, u), new_cert));
            }
            //cout << "check is: " << check << "\n";
            for (int j = 1; j <= 8; ++j) {
                if(!seen[u][j] && check && new_cert[j]) {
                    pq.push(make_pair(edge(d + weight, u), new_cert));
                }
            }
        }
    }
    cout << "-1\n";
    return;
}
// n computers
// m edges
// k certs

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    for(int i = 1; i <= m; i++) {
        int a , b , c;
        cin >> a >> b >> c;
        g[a].push_back(edge(c, b));
        g[b].push_back(edge(c, a));
    }

    for (int i = 1; i <= k; ++i) {
        int f;
        cin >> f;
        for (int j = 1; j <= f; ++j) {
            int node;
            cin >> node;
            gives[node][i] = true;
        }
    }

    for (int i = 1; i <= k; ++i) {
        int gg;
        cin >> gg;
        for (int j = 1; j <= gg; ++j) {
            int node;
            cin >> node;
            requires[node][i] = true;
        }
    }
    dikstras(n);
    return 0;
}