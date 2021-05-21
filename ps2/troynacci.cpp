#include<iostream>

using namespace std;
#define N 100010
long long m = 1e9 + 7;

long long f[N];
long long x[N];
long long flips[N];


int main() {
    int n,q;
    long long a,b;

    cin >> n >> q;
    cin >> f[1] >> f[2];
    cin >> a >> b;

    //compute troynacci for 1 - n
    for (int i = 3; i <= n+1; ++i) {
        f[i] = ((a*f[i-2] % m) + (b*f[i-1] % m)) % m;
    }

    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
    }

    for (int i = 1; i <= q; ++i) {
        int l, r;
        cin >> l >> r;

        flips[l] = (flips[l] + f[1]) % m;
        if (l == r) {
            flips[r+1] = (flips[r+1] + m - (b*f[1] % m)) % m;
            flips[r+2] = (flips[r+2] + m - (a*f[1] % m)) % m;
        } else {
            flips[l+1] = (flips[l+1] + f[2]) % m;
            flips[l+1] = (flips[l+1] + m - ((b * f[1]) % m)) % m;
            flips[r+1] = (flips[r+1] + m - f[r-l + 2]) % m;
            flips[r+2] = (flips[r+2] + m - ((a * f[r-l + 1]) % m)) % m;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (i == 1) {
            x[i] = (x[i] + flips[i]) % m;
        } else if (i == 2) {
            flips[i] = (flips[i] + b*flips[i-1]) % m;
            x[i] = (x[i] + flips[i]) % m;
        } else {
            flips[i] = (flips[i] + a*flips[i-2]) % m;
            flips[i] = (flips[i] + b*flips[i-1]) % m;
            x[i] = (x[i] + flips[i]) % m;
        }
        if (i == n) {
            cout << x[i] << "\n";
        } else {
            cout << x[i] << " ";
        }
    }

    return 0;
}
