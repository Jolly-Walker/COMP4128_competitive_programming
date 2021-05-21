#include <iostream>
using namespace std;
int main() {
    int x;
    cin >> x;
    if (x <= 2) {
        cout << 1 << "\n";
        return 0;
    }
    int lo = 1;
    int hi = 1;
    int count = 1;
    int sum = 0;
    while (hi <= (x+1)/2) {
        // calculate sum


        // check sum
        if (sum == x) {
            ++count;
            ++hi;
            lo = hi;
            sum = lo;
        }
    }
  return 0;
}

int calculate_sum(int lo, int hi) {
    int sum = 0;
    return
}
