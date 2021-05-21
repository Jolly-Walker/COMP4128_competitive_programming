#include <bits/stdc++.h>
using namespace std;


#define maxn 200005

struct my_key {
    int location;
    int can_open;
};

vector<int> graph[maxn];
int depth[maxn];
int n,m;
bool seen[maxn];
bool unlocked[maxn];
my_key keys[605];

int max_depth = 0;
//dfs to get depth array
void dfs_for_depth(int u, int curr_depth) {
    if (seen[u]) return;
    seen[u] = true;
    depth[u] = curr_depth;
    max_depth = max(max_depth, curr_depth);
    for(vector<int>::iterator it = graph[u].begin(); it != graph[u].end(); ++it) {
        dfs_for_depth(*it, curr_depth + 1);
    }
}
void dfs(int u, int curr_depth) {
    if (seen[u]) return;
    seen[u] = true;
    for (int i = 0; i < m; ++i) {
        if (keys[i].location == u) {
            unlocked[keys[i].can_open] = true;
        }
    }
    for(vector<int>::iterator it = graph[u].begin(); it != graph[u].end(); ++it) {
        if (unlocked[*it]) {
            dfs(*it, curr_depth + 1);
        }
    }
}

int main() {
    cin >> n >> m;
    unlocked[1] = true;
    for (int i = 2; i <= n; ++ i) {
        int tmp;
        cin >> tmp;
        graph[tmp].push_back(i);
    }
    for (int i = 0; i < m; ++i) {
        my_key k;
        cin >> k.location;
        int num;
        cin >> num;
        cin >> k.can_open;
        keys[i] = k;
    }
    dfs_for_depth(1,0);
    fill(seen,seen+maxn, false);
    dfs(1,0);
    for (int i = 1; i <= n; ++i) {
        if (!seen[i]) {
            cout <<"NO\n";
            for (int dept = 0; dept <= max_depth; ++dept) {
                bool fully_explored = true;
                for (int j = 1; j <= n; ++j) {
                    if (depth[j] == dept && !seen[j]) {
                        fully_explored = false;
                        break;
                    }
                }
                if (!fully_explored) {
                    cout << dept-1 << "\n";
                    return 0;
                }
            }
        }
    }
    cout << "YES\n";
    
    return 0;
}