//#include<bits/stdc++.h>
#include<iostream>
using namespace std;
//no max number of nodes given in question??
#define maxn 100005

int parent[maxn];
bool vertex[maxn];
bool checks = true;
int cases = 1;

void reset() {
    for(int i = 0; i < maxn; ++i) {
        parent[i] = i;
        vertex[i] = false;
    }
    checks = true;
}

int root(int x) {
    if (parent[x] == x) return x;
    //path compression
    parent[x] = root(parent[x]);
    return parent[x];
}

void join(int x, int y) {
    int root1 = root(x);
    int root2 = root(y);
    if (root1 == root2) {
        //double path
        checks = false;
    } else {
        parent[root2] = root1;
    }
}

void check() {
    if (checks) {
        int root_count = 0;
        for(int i = 0; i < maxn; ++i) {
            if(vertex[i]) {
                if (parent[i] == i) {
                    ++root_count;
                }
            }
        }
        if (root_count <= 1) {
            cout << "Case " << cases << " is a tree.\n";
            return;
        }
    }
    cout << "Case " << cases << " is not a tree.\n";
}

int main() {
    int x, y;
    reset();
    while(1) {
        cin >> x >> y;
        if (x == -1 && y == -1) {
            break;
        }
        if (x == 0 && y == 0) {
            check();
            reset();
            ++cases;
            continue;
        }
        vertex[x] = true;
        vertex[y] = true;
        join(x,y);

    }
    return 0;

}