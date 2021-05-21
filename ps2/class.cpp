#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;
pair<int,int> a[200005];
multiset<int> m;
bool f(const pair<int, int> &lhs, const pair<int, int> &rhs) {
    if (lhs.second == rhs.second) {
        return lhs.first < rhs.first;
    } else {
        return lhs.second < rhs.second;
    }
}

int main() {
    int k, n;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        int start, end;
        cin >> start >> end;
        a[i] = {start,end};
    }
    sort(a, a+n, f);

    int count = 0;
    for(int i = 0; i < n; ++i) {
        auto it = m.lower_bound(-a[i].first);

        if (it == m.end()) {
            if ((int)m.size() < k) {
                m.insert(-a[i].second - 1);
                ++count;
            }
        } else {
            m.erase(it);
            m.insert(-a[i].second - 1);
            ++ count;
        }
    }

    cout << count << "\n";
    return 0;
}
