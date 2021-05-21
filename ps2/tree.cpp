#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

// trying out array representation of trees
//  at most 2^17 * 2 nodes which is ~262k
int tree[300005];

void make_tree(int i, int lo, int hi, int level) {
    // leaf node
    if (lo == hi) {
        cin >> tree[i];
        return;
    }

    int mid = (lo + hi)/2;
    make_tree(2 * i    , lo,      mid, level - 1);
    make_tree(2 * i + 1, mid + 1, hi,  level - 1);

    if (level % 2 == 0) {
        tree[i] = tree[2 * i] ^ tree[2 * i + 1];
    } else {
        tree[i] = tree[2 * i] | tree[2 * i + 1];
    }
}

void update_tree(int i, int lo, int hi, int pos, int new_data, int level) {
    //base
    if (lo == hi) {
        tree[i] = new_data;
        return;
    }

    int mid = (lo + hi)/ 2;

    if (pos <= mid) {
        update_tree(2*i, lo, mid, pos, new_data, level - 1);
    } else {
        update_tree(2*i + 1, mid + 1, hi, pos, new_data, level - 1);
    }

    if (level % 2 == 0) {
        tree[i] = tree[2 * i] ^ tree[2 * i + 1];
    } else {
        tree[i] = tree[2 * i] | tree[2 * i + 1];
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    int size = pow(2, n);
    make_tree(1, 1, size, n);

    for (int i = 0; i < m; ++i) {
        int pos, new_data;
        cin >> pos >> new_data;
        update_tree(1, 1, size, pos, new_data, n);
        cout << tree[1] << "\n";
    }
    return 0;
}
