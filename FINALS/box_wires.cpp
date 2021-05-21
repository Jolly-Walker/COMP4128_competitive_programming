#include<bits/stdc++.h>
using namespace std;

#define maxn 100010
#define double_maxn 200020
const long long mod  = 1e9 + 7;
typedef long long LL;

int wires[4][maxn];

stack<int> numbers;
bool seen[double_maxn];
int main() {
    int num_each_side;
    cin >> num_each_side;
    
    
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < num_each_side; ++j) {
            cin >> wires[i][j];
            if (seen[wires[i][j]]) {
                int tmp = numbers.top();
                if (tmp != wires[i][j]) {
                    cout << "NO\n";
                    return 0;
                }
                numbers.pop();
            } else {
                seen[wires[i][j]] = true;
                numbers.push(wires[i][j]);
            }
        }
    }
    cout << "YES\n";
    return 0;
}