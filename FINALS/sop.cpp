#include<bits/stdc++.h>
using namespace std;

#define maxn 100010
const long long mod  = 1e9 + 7;
typedef long long LL;

int group_size[105];

int num_seats;
int num_groups;

bool check(int distancing) {
    int row1 = 0;
    int row2 = 0;

    for (int i = 0; i < num_groups; ++i) {
        int g = group_size[i];
        int g2 = g + distancing;
        if (row1 == num_seats) {
            if (row1 >= g) {
                row1 -= g;
                continue;
            }
        }
        if (row1 >= g2) {
            row1 -= g2;
            continue;
        }
        if (row2 == num_seats) {
            if (row2 >= g) {
                row2 -= g;
                continue;
            }
        }
        if (row2 >= g2) {
            row2 -= g2;
            continue;
        }
        return false;
    }
    return true;
}
int main() {

    cin >> num_seats >> num_groups;

    for (int i = 0; i < num_groups; ++i) {
        cin >> group_size[i];
    }
    sort(group_size, group_size + num_groups, greater<int>());

    int left = 0;
    int right = 10001;
    while (right - left != 1) {
        int mid = (left + right)/2;

        if (check(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (left == 0) {
        if (!check(0)) {
            cout << "-1\n";
            return 0;
        }
    }
    cout << left << "\n";
    return 0;
}