#include <iostream>
#include <vector>
using namespace std;
int main() {
    int numOfTests;
    cin >> numOfTests;
    for (int testNum = 0; testNum < numOfTests; ++testNum) {
        int numOfCoins;
        cin >> numOfCoins;
        if (numOfCoins == 1) {
            cout << "1\n";
            continue;
        }
        vector<int> coins;
        for (int x = 0; x < numOfCoins; ++x) {
            int tmp;
            cin >> tmp;
            coins.push_back(tmp);
        }
        int sum = coins[0];
        int count = 1;
        for (int i = 1; i < numOfCoins - 1; ++i) {
            if (coins[i] + sum < coins[i+1]) {
                ++count;
                sum += coins[i];
            }
        }
        cout << count + 1 << "\n";
    }
    return 0;
}
