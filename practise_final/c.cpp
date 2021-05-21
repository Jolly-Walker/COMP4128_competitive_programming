#include <iostream>
#include <cstdlib>
#include <cstring>
#include <map>

#define MOD 1000000007

using namespace std;

int s[1000000];
int n;

typedef long long ll;

ll mypow(ll x, ll k) {
  if (k == 0) return 1;

  ll a = mypow(x, k/2);
  a = (a*a) % MOD;
  if (k%2 == 1) a = (a*x) % MOD;
  return a;
}

ll inv(ll x) {
  // By Fermat's little theorem, a^(p-2) is the inverse of a mod p
  return mypow(x, MOD-2);
}

ll fac[1000001];

map<int, int> c;

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> s[i];
    fac[0] = 1;
    for (ll i = 1; i <= n; ++i) fac[i] = (fac[i-1] * i) % MOD;

    for (int i = 0; i < n; ++i) c[s[i]-'a']++;
    ll a = fac[n];
    ll a_ = 1;
    for (auto p : c) a_ *= fac[p.second], a_ %= MOD;
    a *= inv(a_);
    a %= MOD;
    cout << a << '\n';
    return 0;
}

