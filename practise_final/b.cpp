// Ispiti: COCI 06 contest 4 problem 6
// https://dmoj.ca/problem/coci06c4p6
// subtask 2: 1 <= b <= 100

#include <iostream>
#include <utility>
#include <cassert>
#include <set>

using namespace std;

int n, c, a[200001], b[200001], mb;

set<pair<int, int>> v[200001];
set<pair<int, int>> vv;

int main() {
    cin >> n;
    while (n --> 0) {
        char o;
        cin >> o;
        if (o == 'D') {
            ++c;
            cin >> a[c] >> b[c];
            if (b[c] > 100) {
                cerr << "B over 100\n";
                assert(false);
            }
            mb = max(mb, b[c]);
            v[b[c]].emplace(a[c], c);
            if (vv.count({a[c], b[c]})) {
                cerr << "duplicated pair on line " << c << '\n';
                assert(false);
            }
            vv.insert({a[c], b[c]});
        }
        else if (o == 'P') {
            int i;
            cin >> i;
            for (int B = b[i]; B <= mb; ++B) {
                auto m =
                    B == b[i]
                    ? v[B].upper_bound({ a[i], 2e9 })
                    : v[B].lower_bound({ a[i], 0 });
                if (m != v[B].end()) {
                    cout << m->second << '\n';
                    goto success;
                }
            }
            cout << "RIP\n";
success:
            ;
        }
        else {
            cerr << "invalid data\n";
            assert(false);
        }
    }
    return 0;
}

