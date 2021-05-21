#include <bits/stdc++.h>

using namespace std;
#define maxn 100010

int pos[maxn];

// n friends
// q queries

// subtask point update point query
// just do binary search
// full task range update point query
// need to binary search the left and right to get the range of friends to update
// then update using lazy prop
// sadly not enough time to do that 30mins left + I code slowly :(

void update(int posi, int dist, int left, int right) {
    //cout << left << " : l , r: " <<  right << "\n";
    if (left+1 == right) {
        //cout << "posi:" << posi << " pos_left " << pos[left] <<"\n";
        //cout << "left: " << left << "\n";
        if (pos[left] == posi) {
            //cout << "updated pos:" << left << "\n";
            pos[left] = pos[left] + dist;
        }
        return;
    }
    int mid = (left + right)/2;
    if (posi < pos[mid]) {
        update(posi,dist,left,mid);
    } else {
        update(posi,dist,mid,right);
    }
}

int main() {
    int n, q;

    cin >> n >> q;
    
    for (int i = 0; i < n; ++i) {
        cin >> pos[i];
    }

    for (int i = 0; i < q; ++i) {
        int left;
        int right;
        int dist;
        cin >> left >> right >> dist;
        update(left, dist, 0, n);
    }

    for (int i = 0; i < n-1; ++ i) {
        cout << pos[i] << " ";
    }
    cout << pos[n-1] << "\n";
    return 0;
}