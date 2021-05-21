#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>


/*
    1) Get the MST of the graph
    if edge is in the MST --> answer is mst total weight
    if edge is not in MST --> calculate the LCA of the 2 endpoints of the edge to find the largest weight
                              answer is (mst_weight + curr_edge.w - largest_edge.w)

*/
using namespace std;
#define maxn 200005

struct edge {
    int u;
    int v;
    long long w;
    bool in_tree;
    int pos;
};

bool operator<(const edge& a, const edge& b) {
    return a.w < b.w;
}

bool f(const edge& a, const edge& b) {
    return a.pos < b.pos;
}
edge edges[maxn];
vector<pair<int,int>> g_mst[maxn];
int parent[maxn];
int depth[maxn];
int subtree_size[maxn];
int n,m;
bool seen[maxn];
pair<int,int> parent_lca[maxn][18]; // log 200005 ~= 17.6 -> 18
int my_log[maxn];

//dfs to get depth array
void dfs(int u, int curr_depth, int parent_node, int parent_weight) {
    if (seen[u]) return;
    seen[u] = true;
    depth[u] = curr_depth;
    parent_lca[u][0].first = parent_weight;
    parent_lca[u][0].second = parent_node;
    for(vector<pair<int,int>>::iterator it = g_mst[u].begin(); it != g_mst[u].end(); ++it) {
        // parent_lca[it->second][0].first = it->first;
        // parent_lca[it->second][0].second = u;
        dfs(it->second, curr_depth + 1, u , it->first);
    }
}

//parent[u][k] is the 2^k-th parent of u
void preprocess () {
    for ( int i = 1; i <= n; i ++) {
        // assume parent[i][0] ( the parent of i) is already filled in
        for ( int j = 1; (1 << j) < n; j ++) {
            parent_lca[i][j].first = -1;
            parent_lca[i][j].second = -1;
        }
    }
    // fill in the parent for each power of two up to n
    for ( int j = 1; (1 << j) < n; j ++) {
        for ( int i = 1; i <= n; i ++) {
            if ( parent_lca[i][j-1].second != -1) {
                // the 2^j- th parent is the 2^(j -1) -th parent of the 2^(j -1) -th parent
                parent_lca[i][j].first = max(parent_lca[i][j-1].first, parent_lca[parent_lca[i][j-1].second][j-1].first);
                parent_lca[i][j].second = parent_lca[parent_lca[i][j -1].second][j -1].second;
            }
        }
    }
}

int lca ( int u, int v) {
    int largest_weight = -1;
    // make sure u is deeper than v
    if (depth[u] < depth[v]) swap(u,v);
    // cout << u << " "<< v << "\n";
    // cout << depth[u] << " " << depth[v] << "depth 1\n";
    // log[i] holds the largest k such that 2^k <= i
    for ( int i = my_log[depth[u]]; i >= 0; i--) {
        // repeatedly raise u by the largest possible power of two until it is the same depth as v
        // cout << depth[u] << " " << depth[v] << "depth 2\n";
        // cout << i << " i\n";
        if ( depth[u] - (1 << i) >= depth[v]) {
            // cout << u << " \n";
            // cout << parent_lca[u][1].second << " = parent_lca[u][1]\n";
            largest_weight = max(largest_weight, parent_lca[u][i].first);
            u = parent_lca[u][i].second;
            // cout << u << " is u\n";
            // cout << depth[u] << " " << depth[v] << "depth 3\n";
        }
    }

    if (u == v) 
        return largest_weight;

    for (int i = my_log[depth[u]]; i >= 0; i--) {
        if (parent_lca[u][i].second != -1 && parent_lca[u][i].second != parent_lca[v][i].second) {
            largest_weight = max(largest_weight,parent_lca[u][i].first);
            largest_weight = max(largest_weight,parent_lca[v][i].first);
            // raise u and v as much as possible without having them coincide
            // this is important because we ’re looking for the lowest common ancestor , not just any
            u = parent_lca[u][i].second;
            v = parent_lca[v][i].second;
            // cout << u << " " << v << "\n";
            // cout << depth[u] << " " << depth[v] << "depth \n";
        }
    }
    // u and v are now distinct but have the same parent , and that parent is the LCA
    largest_weight = max(largest_weight,parent_lca[u][0].first);
    largest_weight = max(largest_weight,parent_lca[v][0].first);
    return largest_weight;
}

// log[i] holds the largest k such that 2^k <= i
void make_log() {
    //2^0 <= 1
    my_log[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if((1 << (my_log[i - 1] + 1)) <= i ) {
            my_log[i] = my_log[i-1] + 1;
        } else {
            my_log[i] = my_log[i-1];
        }
    }
}

void init() {
    for(int i = 1; i <= n; ++i) {
        parent[i] = i;
        subtree_size[i] = 1;
    }
}
int root (int x) {
    if (parent[x] == x) return x;
    return root(parent[x]);
}

void join (int x, int y) {
    int root1 = root(x);
    int root2 = root(y);
    if (root1 == root2) {
        return;
    } else if(subtree_size[root1] < subtree_size[root2]) {
        parent[root1] = root2;
        subtree_size[root2] += subtree_size[root1];
    } else {
        parent[root2] = root1;
        subtree_size[root1] += subtree_size[root2];
    }
}

long long mst () {
    sort (edges , edges+m); // sort by increasing weight
    long long total_weight = 0;
    for ( int i = 0; i < m; i ++) {
        edge& e = edges[i];
        // if the endpoints are in different trees , join them
        if (root (e.u) != root (e.v)) {
            total_weight += e.w;
            join (e.u, e.v);
            g_mst[e.u].push_back(make_pair(e.w,e.v));
            g_mst[e.v].push_back(make_pair(e.w,e.u));
            e.in_tree = true;
        }
    }
    //unsort the edges;
    sort(edges, edges+m, f);
    return total_weight;
}


int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        edge e;
        cin >> e.u >> e.v >> e.w;
        e.in_tree = false;
        e.pos = i;
        edges[i] = e;
    }
    init();
    long long min_weight = mst();
    dfs(1,1, -1,-1);
    make_log();
    preprocess();
    for (int i = 0; i < m; ++i) {
        if (edges[i].in_tree) {
            cout << min_weight << "\n";
        } else {
            long long to_delete_edge = lca(edges[i].u, edges[i].v);
            long long ans = min_weight - to_delete_edge + edges[i].w;
            cout << ans << "\n" ;//<< " is from " << min_weight << " - " << to_delete_edge << " + " << edges[i].w << "\n";
        }
    }
    return 0;
}