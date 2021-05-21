#include<iostream>
#include<algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using namespace std;
#define maxn 200010
typedef long long LL;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int data[maxn];
vector<int> edges[maxn];
int startRange[maxn];
int endRange[maxn];
int totId = 0;
vector<ordered_set> tree[4*maxn];

void update(int target, int val, int index, int left, int right) {
    if (right - left == 1) {
        tree[index].
    }
}
void dfs(int i, int prev) {
    ++totId
	startRange[i] = totId;
	for (int nxt : edges[i]) {
		if (prev == nxt) continue;
		dfs(nxt, i);
	}
	out[i] = totId;
}

update_node(int i, int val) {
    update(index_in_range_tree[i],val);
}

int query_subtree(int i) {
    return query(startRange[i], endRange[i]);
}
int main() {
    int n,q;
    cin >> n >> q;
    
    for (int i = 0; i < n; ++i) {
        cin >> data[i];
    }

    for (int i = 0; i < n-1; ++i) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    dfs(0, 0);
    for (int i = 0; i < n; ++i) {
        makeTree(i, val[i]);
    }
    for (int i = 0; i < q; ++i) {
        int a, s;
        cin >> a >> s;
        cout << query(a, s) << "\n";
        buildTree(a, s);
    }
    return 0;
}