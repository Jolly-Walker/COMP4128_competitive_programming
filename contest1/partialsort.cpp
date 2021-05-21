#include <iostream>
#include <algorithm>
using namespace std;
int a[10010];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[j + (i*n)];
        }
    }
    sort(a, a + (n*n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            cout << a[j + (i*n)] << " ";
        }
        cout << a[n-1 + i*n]<< "\n";
    }
    return 0;
}
