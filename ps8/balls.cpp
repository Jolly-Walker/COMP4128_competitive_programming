#include<bits/stdc++.h>
using namespace std;

#define maxn 1005
typedef long long LL;
LL const mod = 1e9 + 7;

int balls[maxn];

LL f[maxn];

LL pow_m(LL x, LL n, LL m) {
    if (n == 0) return 1;

    LL a = pow_m(x,n/2,m);
    a = a * a % m;
    if (n%2 == 1) a = a * x % m;
    return a;
}
LL inv(LL x) {
    // By Fermat ’s little theorem , a^(p -2) is the inverse of a mod p
    return pow_m(x, mod -2 , mod);
}

LL comb(int n, int k) {
    // factorials
    LL res =(f[n] * inv(f[n-k])) % mod;
    res =( res * inv(f[k])) % mod;
    return res;
}

int main() {
    int number_of_balls;
    cin >> number_of_balls;
    LL total = 0;
    for(int i = 1; i <= number_of_balls; ++i) {
        cin >> balls[i];
        total += balls[i];
    }
    f[0] = 1;
    for( int i = 1; i < maxn; i ++) {
        f[i] =(i*f[i -1]) % mod;
    }
    LL ans = 1;
    for (int i = number_of_balls; i >= 1; --i) {
        ans = (ans * comb(total - 1, balls[i]-1)) % mod;
        total -= balls[i];
    }
    cout << ans << "\n";
    return 0;
}