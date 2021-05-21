#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define maxn 300010
const LL mod = 1000000007;
vector<int> edges[maxn];
LL c[2][maxn];
LL val[2];
LL L[maxn];
LL R[maxn];
LL d[maxn];
LL totId;

//range update, point query
void update(int i){
    while(i <= totId){
        c[0][i] += val[0];
        c[1][i] += val[1];
        c[0][i] %= mod;
        c[1][i] %= mod;
        i += (i&-i);
        cout << i << "\n"; 
    }
}

// void update(int target, LL val, int index, int left, int right) {

//     if (left == target && right == target + 1) {
//         tree[index].sum = val;
//         tree[index].max = val;
//         tree[index].min = val;
//         tree[index].increasing = true;
//         tree[index].decreasing = true;
//         //cout << index << " index and tar: "<< target << " is now val: " << val << "\n";
//         return;
//     }
//     int mid = (left + right)/2;
//     if (target < mid) {
//         update(target, val, index*2, left, mid);
//     } else {
//         update(target, val, index*2+1, mid, right);
//     }
//     recalculate(index);
// }

LL query(int i){
    LL sum[2] = {0};
    LL depth = d[i];
    i = L[i];
    while(i){
        sum[0] += c[0][i];
        sum[1] += c[1][i];
        sum[0] %= mod;
        sum[1] %= mod;
        i -= i&-i;
    }
    return ((sum[0] - depth*sum[1])%mod + mod)%mod;
}

void dfs(int i,int depth){
    ++totId;
    L[i] = totId;
    d[i] = depth;
    for(int nxt: edges[i]) {
        if (nxt == i) continue;
        dfs(nxt,depth+1);
    }
    R[i] = totId;
}

int main(){
    int n;
    cin >> n;
    for (int i = 0; i < n-1; ++i) {
        int parent;
        cin >> parent;
        edges[parent].push_back(i);
    }
    dfs(1,0);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int num, v, x, k;
        cin >> num;
        if (num == 1) {
            cin >> v >> x >> k;
            val[0] = (x + d[v]*k) % mod;
            val[1] = k;
            update(L[x]);
            val[0] = -val[0];
            val[1] = -val[1];
            update(R[x]+1);
        } else {
            cin >> v;
            cout << query(v) << "\n";
        }
    }
    return 0;
}