#include <bits/stdc++.h>
using namespace std;
#define maxn 505
typedef long long LL;

LL my_graph[maxn][maxn];
int v_to_delete[maxn];
LL ans[maxn];
bool available[maxn];

//just do it backwards
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i ) {
        for (int j = 1; j <= n; ++j) {
            cin >> my_graph[i][j];
        }
    }

    for (int i = 1; i <= n; ++i ) {
        cin >> v_to_delete[i];
    }

    for (int i = n; i >= 1; --i) {
        int add = v_to_delete[i];
        available[add] = true;
        for (int j = 1; j <=n; ++j) {
            for (int k = 1; k <=n; ++k) {
                my_graph[j][k] = min(my_graph[j][k], my_graph[j][add] + my_graph[add][k]);
                if (available[j] && available[k]) {
                    ans[i] += my_graph[j][k];
                }
            }
        }
    }
    for (int i = 1; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << ans[n] << "\n";
    return 0;
}