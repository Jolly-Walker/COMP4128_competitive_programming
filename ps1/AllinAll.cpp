#include <iostream>
using namespace std;
int main() {
    string str1, str2;
    while(cin >> str1 >> str2) {
    int str1_pos = 0;
    bool x = false;
    for (int i = 0; i < (int)str2.length(); ++i) {
        if (str2[i] == str1[str1_pos]) {
            str1_pos++;
            if (str1_pos >= (int)str1.length()) {
                x = true;
                break;
            }
        }
    }
    x ? cout << "Yes\n" : cout << "No\n";
    }
  return 0;
}
