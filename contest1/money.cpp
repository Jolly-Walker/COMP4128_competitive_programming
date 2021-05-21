#include <iostream>

using namespace std;
int h[505][45];
int profit[505][45];
int max_money[45];
int n,k,s;

int max(int a, int b) { return (a > b) ? a : b; }

int top2(int W, int year)
{
    int final_profit = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                if ((profit[i][year] > final_profit) && (h[i][year] <= W)) {
                    final_profit = profit[i][year];
                }
            } else {
                if ((profit[i][year] + profit[j][year] > final_profit) && (h[i][year] + h[j][year] <= W)) {
                    final_profit = profit[i][year] + profit[j][year];
                }
            }
        }
    }
    return final_profit;
}

int main() {
    cin >> n >> k >> s;

    for (int i = 0; i < n; ++i) {
        cin >> h[i][0];
        for (int j = 1; j <= k; ++j) {
            cin >> h[i][j];
            profit[i][j-1] = h[i][j] - h[i][j-1];
        }
    }

    max_money[0] = s;
    for (int i = 1; i <= k; ++i) {
        max_money[i] = top2(max_money[i-1], i-1) + max_money[i-1];
    }

    cout << max_money[k] << "\n";
    return 0;
}
