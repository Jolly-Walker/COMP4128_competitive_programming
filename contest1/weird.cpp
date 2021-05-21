#include <iostream>
#include <algorithm>
using namespace std;
char s[5000005];
int n,k;
int main() {
    cin >> n >> k;
    cin >> s[0];
    int cur = 0;
    int next = 0;
    int dist = 0;
    int jumps = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        ++dist;
        if (s[i] == '1') {
            next = i;
        }
        if (dist == k) {
            if (next > cur) {
                dist -= (next - cur);
                cur = next;
                ++jumps;
            } else {
                break;
            }
        }
    }

    if (cur == n) {
        cout << jumps << "\n";
    } else if (next == n) {
        cout << jumps + 1 << "\n";
    } else {
        cout << "-1\n";
    }
    return 0;
}
