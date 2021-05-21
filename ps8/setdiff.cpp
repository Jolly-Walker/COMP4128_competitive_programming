#include<bits/stdc++.h>
using namespace std;

#define maxn 100010
const long long mod  = 1e9 + 7;
long long my_pow[maxn];
long long my_set[maxn];

int main() {
    my_pow[0] = 1;
    long long x;
    for (int i = 1; i < maxn; ++i) {
        x = my_pow[i-1] * 2;
        x = x % mod;
        my_pow[i] = x;
    }

    int cases;
    cin >> cases;
    while (cases) {
        int set_size;
        cin >> set_size;
        for (int i = 0; i < set_size; ++i) {
            cin >> my_set[i];
        }
        sort(my_set, my_set + set_size);
        long long ans = 0;
        long long tmp;
        for (int i = 0; i < set_size; ++i) {
            tmp = my_pow[i] - my_pow[set_size - i - 1];
            if (tmp < 0) {
                tmp += mod;
            }
            tmp = (tmp * my_set[i]) % mod;
            // cout << tmp << " is tmp\n";
            ans = (ans + tmp) % mod;
        }
        cout << ans << "\n";
        --cases;
    }
}