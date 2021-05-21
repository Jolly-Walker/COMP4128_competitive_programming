#include<bits/stdc++.h>
using namespace std;

#define maxn 105
typedef long long LL;
LL const mod = 1e9 + 7;
struct Array_2d {
    LL a[maxn][maxn];
    Array_2d() {};
};

LL number_of_gems;
int magic_split;
Array_2d ori;
Array_2d ans_product;
Array_2d my_mul(Array_2d lhs, Array_2d rhs) {
    Array_2d tmp;
    for (int i = 0; i < magic_split; ++i) {
        fill(tmp.a[i], tmp.a[i] + maxn, (LL)0);
    }
    for(int i = 0; i < magic_split; ++i) {
        for(int j = 0; j < magic_split; ++j) {
            for(int k = 0; k < magic_split; ++k) {
                tmp.a[i][j] = (tmp.a[i][j] + lhs.a[i][k] * rhs.a[k][j]) % mod;
            }
        }
    }
    return tmp;
}

Array_2d my_pow(Array_2d x, LL n) {
    if (n == 1) return x;
    Array_2d a = my_pow(x, n/2);
    a = my_mul(a,a);
    if (n%2 == 1) a = my_mul(a,x);
    return a;
}

int main() {

    cin >> number_of_gems >> magic_split;
    if (number_of_gems < magic_split) {
        cout << "1\n";
        return 0;
    }
    if (number_of_gems == magic_split) {
        cout << "2\n";
        return 0;
    }
    for (int i = 1; i < magic_split ; ++i) {
        ori.a[i][i-1] = 1;
    }
    ori.a[0][magic_split-1] = 1;
    ori.a[0][0] = 1;

    for (int i = 0; i < magic_split; ++i) {
        ans_product.a[i][0] = 1;
    }
    Array_2d ans = my_pow(ori,number_of_gems-magic_split+1);
    Array_2d ans2 = my_mul(ans,ans_product);
    cout << ans2.a[0][0] << "\n";
}