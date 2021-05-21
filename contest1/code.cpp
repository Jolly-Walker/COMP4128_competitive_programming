#include <iostream>
#include <deque>
#include <stdlib.h>

using namespace std;
char code[105];
int n,c,m;
int f[11];
deque<int> question_pos;

// checks all 3 digit combinators
bool check(int pos) {
    // check [..*]..
    if (pos-2 >= 0 && pos < n) {
        int hundreds = code[pos-2] - '0' ;
        int tens = code[pos-1] - '0';
        int ones = code[pos] - '0';
        int test_num = hundreds*100 + tens*10 + ones;
        if ((test_num ^ c) % m == 0) {
            return false;
        }
    }

    // check .[.*.].
    if (pos + 1 < n && pos - 1 >= 0) {
        if (code[pos + 1] != '?') {
            int hundreds = code[pos-1] - '0';
            int tens = code[pos] - '0';
            int ones = code[pos + 1] - '0';
            int test_num = hundreds*100 + tens*10 + ones;
            if ((test_num ^ c) % m == 0) {
                return false;
            }
        }
    }
    // check ..[*..]
    if (pos + 2 < n && pos >= 0) {
        if (code[pos + 2] != '?' && code[pos + 1] != '?') {
            int hundreds = code[pos] - '0';
            int tens = code[pos + 1] - '0';
            int ones = code[pos + 2] - '0';
            int test_num = hundreds*100 + tens*10 + ones;
            if ((test_num ^ c) % m == 0) {
                return false;
            }
        }
    }
    return true;
}

bool go() {
    if (question_pos.empty()) {
        return true;
    }
    int my_pos = question_pos.front();
    question_pos.pop_front();

    // try the available numbers in the '?' at my_pos
    // if it doesnt break any rules go to the next '?'
    for (int i = 0; i < 10; ++i) {
        if (f[i] == 0) {
            continue;
        }

        code[my_pos] = '0' + i;
        --f[i];
        bool valid = check(my_pos);
        if (valid) {
            bool result = go();
            if (result) {
                return true;
            } else {
                ++f[i];
                code[my_pos] = '?';
            }
        } else {
            code[my_pos] = '?';
            ++f[i];
        }
    }
    question_pos.push_front(my_pos);
    return false;
}
int main() {
    cin >> n >> c >> m;

    for (int i = 0; i < 10; ++i) {
        cin >> f[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> code[i];
        if (code[i] == '?') {
            question_pos.push_back(i);
        }
    }

    if (go()) {
        for (int i = 0; i < n; ++i) {
            cout << code[i];
        }
        cout << "\n";
    } else {
        cout << "-1\n";
    }
    return 0;
}
