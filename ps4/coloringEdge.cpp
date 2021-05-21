#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;
#define maxn 5005

vector<int> g[maxn];
pair<int,int> edges[maxn];
int in_degree[maxn];
int n, m;
int count = 0;
int check() {
    int x = 0;
	queue<int> my_queue;
    //add 'root' nodes
	for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            my_queue.push(i);
        }
    }

	while (!my_queue.empty()) {
		int v = my_queue.front();
        my_queue.pop();
        ++x;
		for (int j : g[v]) {
			--in_degree[j];
            //only add into queue when a vertex has no more incoming edges
			if (in_degree[j] == 0){
                my_queue.push(j);
            }
		}
	}
    
	if (x == n) {
        return true;
    }
	else {
        return false;
    }
}
int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        edges[i] = make_pair(a,b);
        ++in_degree[b];
    }

    if (check()) {
        cout << 1 << "\n";
        for (int i = 1; i < m ; ++i) {
            cout << "1 ";
        }
        cout << "1\n";
    } else {
        // you only need 2 colours
        // all edges heading to node m set as one colour
        // all edges heading to node 1 set as another colour
        cout << 2 << "\n";
        for (int i = 1; i < m ; ++i) {
            if (edges[i].first < edges[i].second) {
                cout << "1 ";
            } else {
                cout << "2 ";
            }
        }
        if (edges[m].first < edges[m].second) {
                cout << "1\n";
            } else {
                cout << "2\n";
        }
    }
    return 0;
}