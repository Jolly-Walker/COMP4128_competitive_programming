#include<bits/stdc++.h>
using namespace std;

#define maxn 100010
const long long mod  = 1e9 + 7;
typedef long long LL;

int n, m, p;
struct edge {
    int v;
    int level;
};

// bool operator<(const edge& a, const edge& b) {
//     return a.w < b.w;
// }

// bool f(const edge& a, const edge& b) {
//     return a.pos < b.pos;
// }
vector<edge> graph[maxn];

bool seen[maxn];
set<int> needed_cities_set; 
int needed_cities[maxn];
//dfs to get depth array
void dfs(int curr, int req_level) {
    if (seen[curr]) return;
    seen[curr] = true;
    //cout << "curr is: " << curr << "\n";
    set<int>::iterator tmp_it = needed_cities_set.find(curr);
    if (tmp_it != needed_cities_set.end()) {
        needed_cities_set.erase(tmp_it);
        if (needed_cities_set.empty()) {
            return;
        }
    }

    for(vector<edge>::iterator it = graph[curr].begin(); it != graph[curr].end(); ++it) {
        if (it->level <= req_level) {
            dfs(it->v, req_level);
        }
    }
    return;
}

void refresh() {
    needed_cities_set.clear();
    fill(seen, seen+maxn, false);
    for (int i = 0; i < p; ++i) {
        needed_cities_set.insert(needed_cities[i]);
    }
}

bool check(int root, int req_level) {
    dfs(root, req_level);
    if (needed_cities_set.empty()) {
        return true;
    } else {
        return false;
    }
    
}
int main() {
    cin >> n >> m >> p;
    for (int i = 0; i < m; ++i) {
        int a;
        int b;
        int level;
        edge e1,e2;
        cin >> a >> b >> level;
        e1.v = b, e1.level = level;
        e2.v = a, e2.level = level;
        graph[a].push_back(e1);
        graph[b].push_back(e2);
    }
    for (int i = 0; i < p; ++i) {
        cin >> needed_cities[i];
        needed_cities_set.insert(needed_cities[i]);
    }
    if (needed_cities_set.size() <= 1) {
        cout << 0 << "\n";
    } else {
        int left = 0;
        int right = 100001;
        while (right - left != 1) {
            refresh();
            double mid = (left + right)/2;
            set<int>::iterator iter = needed_cities_set.find(needed_cities[0]);
            needed_cities_set.erase(iter);
            //cout << mid << "\n";
            if (check(needed_cities[0], mid)) {
                right = mid;
            } else {
                left = mid;
            }
        }
        cout << right << "\n";
    }
    return 0;
}