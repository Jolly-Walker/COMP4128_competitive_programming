#include<iostream>
#include<algorithm>

using namespace std;
#define maxn 100000

int lazyadd[266666];
int sum[266666][3];

//Range update, range query, inclusive


void recalculate(int id) {
    int left = id*2;
    int right = id*2 + 1;
    sum[id][0] = sum[left][0] + sum[right][0];
    sum[id][1] = sum[left][1] + sum[right][1];
    sum[id][2] = sum[left][2] + sum[right][2];

}

void propagate(int id) {
    int left = id*2;
    int right = id*2 + 1;
    
    int tmp;
    //cout << id << " proping\n";
    if (lazyadd[id] == 0) return;
    lazyadd[left] += lazyadd[id];
    lazyadd[left] = lazyadd[left] % 3;
    lazyadd[right] += lazyadd[id];
    lazyadd[right] = lazyadd[right] % 3;

    if (lazyadd[id] == 1) {
        tmp = sum[left][0];
        sum[left][0] = sum[left][2];
        sum[left][2] = sum[left][1];
        sum[left][1] = tmp;

        tmp = sum[right][0];
        sum[right][0] = sum[right][2];
        sum[right][2] = sum[right][1];
        sum[right][1] = tmp;
    } else if (lazyadd[id] == 2) {
        tmp = sum[left][0];
        sum[left][0] = sum[left][1];
        sum[left][1] = sum[left][2];
        sum[left][2] = tmp;
        
        tmp = sum[right][0];
        sum[right][0] = sum[right][1];
        sum[right][1] = sum[right][2];
        sum[right][2] = tmp;
    }
    lazyadd[id] = 0;
    return;
}
void init(int index, int left, int right) {
    if (left == right) {
        sum[index][0] = 1;
        return;
    }
    int mid = (left+right)/2;
    int l_index = index*2;
    int r_index = index*2 + 1;
    init(l_index, left, mid);
    init(r_index, mid+1, right);
    recalculate(index);
}

void update(int uL, int uR, int i, int cLeft, int cRight) {
    if (uL >= cLeft && uR <= cRight) {
        int tmp = sum[i][0];
        sum[i][0] = sum[i][2];
        sum[i][2] = sum[i][1];
        sum[i][1] = tmp;
        ++lazyadd[i];
        lazyadd[i] = lazyadd[i] % 3;
        return;
    }
    propagate(i);
    int mid = (uL + uR) / 2;
    if (cLeft <= mid) {
        update(uL, mid, i * 2, cLeft, cRight);
    }
    if (cRight >= mid+1) {
        update(mid+1, uR, i * 2 + 1, cLeft, cRight);
    }
    recalculate(i);
}

int query ( int qL, int qR, int i, int cLeft, int cRight) {
    if (qL >= cLeft && qR <= cRight) {
        return sum[i][0];
    }
    propagate(i);
    int mid = (qL + qR)/2;

    int ans = 0;
    if (cLeft <= mid)  {
        //cout << qL << "is qL " << mid << "is mid\n";
        ans += query(qL, mid, i*2, cLeft, cRight);
    }
    if (cRight >= mid+1) {
        //cout << qL << "is qR " << mid << "is mid\n";
        ans += query(mid+1, qR, i*2+1, cLeft, cRight);
    }
    return ans;
}

int main() {
    int n,q;
    cin >> n >> q;
    init(1,0,n-1);
    for (int i = 0; i < q; ++i) {
        int t,a,b;
        cin >> t >> a >> b;
        //cout << "command \n";
        if (t == 0) {
            update(0, n-1, 1, a, b);
        } else {
            cout << query(0, n-1, 1, a, b) << "\n";
        }
    }
    return 0;
}