#include<bits/stdc++.h>
using namespace std;

#define maxn 100010

const long long mod  = 1e9 + 7;
typedef long long LL;

LL pow(LL x, LL n, LL m) {
    if (n == 0) return 1;

    LL a = pow(x,n/2,m);
    a = a * a % m;
    if (n%2 == 1) a = a * x % m;
    return a;
}

int main() {
    LL num_to_combine;
    cin >> num_to_combine;
    vector<LL> original = vector<LL>(5);
    
    for(int i = 0; i < 5; ++i) {
        cin >> original[i];
    }

    vector<LL> tmp = vector<LL>(5);

    tmp[0] = pow(original[4], num_to_combine, mod);
    for(int i = 1; i < 5; ++i) {
        tmp[i] = pow(original[i-1], num_to_combine, mod);
    }

    for(int i = 0; i < 4; ++i) {
        cout << ((original[i] * tmp[i]) % mod) << " ";
    }
    cout << ((original[4] * tmp[4]) % mod) << "\n";
    return 0;

}