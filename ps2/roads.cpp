#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

#define N 500005

struct query_struct {
    char query_type;
    int data;
    long long prev_pop;
};

int n, m, q;

int parent[N];
int subtree_size[N];
long long city[N];
long long root_pop[N];
pair<int,int> road[N];
set<pair<long long,int>> regions;
query_struct query[N];
long long ans[N];


void init() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i; subtree_size[i] = 1;
    }
}

int root(int x) {
    return parent[x] == x ? x : parent[x] = root(parent[x]);
}

void join ( int x, int y) {
    x = root (x); y = root (y);
    if (x == y) return ;

    regions.erase({root_pop[x], x});
    regions.erase({root_pop[y], y});

    if ( subtree_size [x] < subtree_size [y]) {
        parent[x] = y;
        subtree_size [y] += subtree_size [x];
        root_pop[y] += root_pop[x];
        regions.insert({root_pop[y],y});
    } else {
        parent[y] = x;
        subtree_size [x] += subtree_size [y];
        root_pop[x] += root_pop[y];
        regions.insert({root_pop[x],x});
    }
}

int main() {
    cin >> n >> m >> q;
    set<int> available;
    for (int i = 1; i <= n ; ++i) {
        cin >> city[i];
    }

    for (int i = 1; i <= m ; ++i) {
        int from , to;
        cin >> from >> to;
        road[i] = {from, to};
        available.insert(i);
    }

    for (int i = 1; i <= q; ++i) {
        cin >> query[i].query_type;
        cin >> query[i].data;
        if (query[i].query_type == 'P') {
            query[i].prev_pop = city[query[i].data];
            cin >> city[query[i].data];
        } else {
            available.erase(query[i].data);
        }
    }

    init();
    for (int i = 1; i <= n; ++i ) {
        root_pop[i] = city[i];
        regions.insert({root_pop[i], i});
    }

    for (auto it = available.begin(); it != available.end(); ++it) {
        join(road[*it].first, road[*it].second);
    }

    auto it = regions.end();
    --it;
    ans[q] = it->first;

    for (int i = q; i > 0; --i) {

        if (query[i].query_type == 'D') {
            join(road[query[i].data].first, road[query[i].data].second);
        } else {
            int curr_root = root(query[i].data);
            regions.erase({root_pop[curr_root], curr_root});
            root_pop[curr_root] -= city[query[i].data];
            city[query[i].data] = query[i].prev_pop;
            root_pop[curr_root] += city[query[i].data];
            regions.insert({root_pop[curr_root], curr_root});
            // cout << "city " << query[i].data << " pop updated to " << query[i].prev_pop << '\n';
        }
        it = regions.end();
        --it;
        ans[i - 1] = it->first;
    }

    for (int i = 1; i <= q; ++i) {
        cout << ans[i] << "\n";
    }
}
