#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;
#define maxn 2005

vector<pair<int,int>> g[maxn];
priority_queue<pair<int ,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
bool in_tree[maxn];
// find the mst and return the largest edge weight
int mst() {
    int max_weight = 0;
    in_tree [1] = true ; // (2)
    for (vector<pair<int,int>>::iterator edge = g[1].begin(); edge != g[1].end(); ++edge) {
        pq.push(make_pair(edge->first, edge->second));
    }
    while (!pq.empty()) { // (3)
        pair<int,int> edge = pq.top();
        pq.pop() ;
        if (in_tree[edge.second]) continue ;
        in_tree [edge.second] = true ;
        max_weight = max(max_weight,edge.first);
        for (vector<pair<int,int>>::iterator edge2 = g[edge.second].begin(); edge2 != g[edge.second].end(); ++edge2) {
            pq.push(make_pair(edge2->first, edge2->second));
        }
    }
    return max_weight ;

}
int main() {
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; ++i) {
        int a, b;
        int c;
        cin >> a >> b >> c;
        g[a].push_back(make_pair(c,b));
        g[b].push_back(make_pair(c,a));
    }

    cout << mst() << "\n";
    return 0;
}