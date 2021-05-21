#include <bits/stdc++.h>

using namespace std;
#define maxn 100010

vector<int> g[maxn];


pair<int,int> edges[maxn];
bool knows[maxn];
// n workers
// m days
// 
int main() {
    int n, m;

    cin >> n >> m;
    
    for(int i = 1; i <= m; i++) {
        int a , b;
        cin >> a >> b;
        edges[i] = make_pair(a,b);
    }

    for (int i = 1; i <= m-1; i++) {
        int count;
        fill(knows, knows + n+5, 0);
        knows[1] = true;
        count = 1;
        for (int j = i; j <=m; ++j) {
            pair<int,int> workers = edges[j];
            //cout << "worker1: "<< knows[workers.first] << " worker2: " << knows[workers.second] << "\n";
            if (knows[workers.first]) {
                if (!knows[workers.second]) {
                    ++count;
                    knows[workers.second] = true;
                }
            } else if (knows[workers.second]) {
                if (!knows[workers.first]) {
                    ++count;
                    knows[workers.first] = true;
                }
            }
        }
        cout << count << " ";
    }
    int count;
    fill(knows, knows + n+5, 0);
    knows[1] = true;
    count = 1;
    for (int j = m; j <=m; ++j) {
        pair<int,int> workers = edges[j];
        if (knows[workers.first]) {
            if (!knows[workers.second]) {
                ++count;
                knows[workers.second] = true;
            }
        } else if (knows[workers.second]) {
            if (!knows[workers.first]) {
                ++count;
                knows[workers.first] = true;
            }
        }
    }
    cout << count << "\n";
    return 0;
}