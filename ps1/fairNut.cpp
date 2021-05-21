#include <iostream>
using namespace std;
int main() {
    long long numberOfStr, strLength;
    char a[500005];
    char b[500005];

    cin >> strLength >> numberOfStr;
    cin >> a >> b;
    long long numberOfprefix = 1;
    long long ans = 0;

    for (long long i = 0; i < strLength ; ++i) {
        numberOfprefix *= 2;

        if (a[i] == 'b') {
            --numberOfprefix;
        }
        if (b[i] == 'a') {
            --numberOfprefix;
        }

        if (numberOfprefix > numberOfStr) {
            numberOfprefix = numberOfStr;
        }
        if (numberOfprefix <= numberOfStr) {
            ans += numberOfprefix;
        } else {
            ans += numberOfStr;
        }

    }
    cout << ans << "\n";
    return 0;
}
