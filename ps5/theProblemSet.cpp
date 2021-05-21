#include<iostream>
#include<algorithm>

using namespace std;
#define maxn 100010
typedef long long LL;

//point update, range query, max, sum, sorted ascending, decending, not inclusive
//no need lazy

struct node {
    LL sum;
    LL max;
    LL min;
    bool increasing;
    bool decreasing;
};

node tree[266666];

bool check_increasing(int left, int right) {
    if (tree[left].increasing && tree[right].increasing) {
        if (tree[left].max <= tree[right].min) {
            return true;
        }
    }
    return false;
}

bool check_decreasing(int left, int right) {
    if (tree[left].decreasing && tree[right].decreasing) {
        if (tree[left].min >= tree[right].max) {
            return true;
        }
    }
    return false;
}
void recalculate(int index) {
    int left = index*2;
    int right = index*2+1;
    tree[index].sum = tree[left].sum + tree[right].sum;
    tree[index].max = max(tree[left].max, tree[right].max);
    tree[index].min = min(tree[left].min, tree[right].min);
    tree[index].increasing = check_increasing(left, right);
    tree[index].decreasing = check_decreasing(left, right);
}

void update(int target, LL val, int index, int left, int right) {

    if (left == target && right == target + 1) {
        tree[index].sum = val;
        tree[index].max = val;
        tree[index].min = val;
        tree[index].increasing = true;
        tree[index].decreasing = true;
        //cout << index << " index and tar: "<< target << " is now val: " << val << "\n";
        return;
    }
    int mid = (left + right)/2;
    if (target < mid) {
        update(target, val, index*2, left, mid);
    } else {
        update(target, val, index*2+1, mid, right);
    }
    recalculate(index);
}

long long query_sum(int qL, int qR, int i, int cLeft, int cRight) {
    if (qL == cLeft && qR == cRight ) {
        return tree[i].sum;
    }

    int mid = (cLeft + cRight ) / 2;
    long long ans = 0;
    if (qL < mid ) ans += query_sum(qL, min (qR, mid ), i * 2, cLeft, mid );
    if (qR > mid ) ans += query_sum(max (qL, mid ), qR, i * 2 + 1, mid, cRight );
    return ans ;
}

long long query_max(int qL, int qR, int i, int cLeft, int cRight) {
    if (qL == cLeft && qR == cRight ) {
        return tree[i].max;
    }

    int mid = (cLeft + cRight ) / 2;
    long long ans = 0;
    long long ans2 = 0;
    if (qL < mid ) ans = query_max(qL, min (qR, mid ), i * 2, cLeft, mid );
    if (qR > mid ) ans2 = query_max(max (qL, mid ), qR, i * 2 + 1, mid, cRight );
    return max(ans,ans2);
}

// pair.first = min, pair.second = max
pair<LL,LL> query_increasing(int qL, int qR, int i, int cLeft, int cRight) {
    // cout << qL << " " << qR << " " << cLeft << " " << cRight << "\n" ;
    if (qL == cLeft && qR == cRight ) {
        if (tree[i].increasing) {
            // cout << "true!\n";
            return make_pair(tree[i].min, tree[i].max);
        } else {
            // cout << "false!\n";
            return make_pair(-1,-1);
        }
    }

    int mid = (cLeft + cRight ) / 2;
    pair<LL,LL> left_ans = {0,0};
    pair<LL,LL> right_ans = {0,0};
    if (qL < mid ) left_ans = query_increasing(qL, min (qR, mid ), i * 2, cLeft, mid );
    if (qR > mid ) right_ans = query_increasing(max (qL, mid ), qR, i * 2 + 1, mid, cRight);

    // cout << left_ans.first << " " << left_ans.second << " " << "\n";
    // increasing is false in children
    if (left_ans.first == -1 && left_ans.second == -1) return left_ans;
    if (right_ans.first == -1 && right_ans.second == -1) return right_ans;

    // only one child called
    if (left_ans.first == 0 && left_ans.second == 0) {
        return right_ans;
    }
    if (right_ans.first == 0 && right_ans.second == 0) {
        return left_ans;
    }

    // both were called
    if (left_ans.second <= right_ans.first) {
        return make_pair(left_ans.first, right_ans.second);
    } else {
        return make_pair(-1,-1);
    }
}

// pair.first = min, pair.second = max
pair<LL,LL> query_decresing(int qL, int qR, int i, int cLeft, int cRight) {
    if (qL == cLeft && qR == cRight ) {
        if (tree[i].decreasing) {
            return make_pair(tree[i].min, tree[i].max);
        } else {
            return make_pair(-1,-1);
        }
    }

    int mid = (cLeft + cRight ) / 2;
    pair<LL,LL> left_ans = {0,0};
    pair<LL,LL> right_ans = {0,0};
    if (qL < mid ) left_ans = query_decresing(qL, min (qR, mid ), i * 2, cLeft, mid );
    if (qR > mid ) right_ans = query_decresing(max (qL, mid ), qR, i * 2 + 1, mid, cRight);

    // increasing is false in children
    if (left_ans.first == -1 && left_ans.second == -1) return left_ans;
    if (right_ans.first == -1 && right_ans.second == -1) return right_ans;

    // only one child called
    if (left_ans.first == 0 && left_ans.second == 0) {
        return right_ans;
    }
    if (right_ans.first == 0 && right_ans.second == 0) {
        return left_ans;
    }

    // both were called
    if (left_ans.first >= right_ans.second) {
        return make_pair(right_ans.first, left_ans.second);
    } else {
        return make_pair(-1,-1);
    }
}

int main() {
    int n,q;
    cin >> n >> q;
    
    for (int i = 0; i < n; ++i) {
        LL d;
        cin >> d;
        update(i, d, 1, 0, n);
    }
    //cout << tree[1].max << " is max and this is sum: " << tree[1].sum << "\n";
    for (int i = 0; i < q; ++i) {
        char command;

        LL a,b;

        cin >> command >> a >> b;
        --a;
        // cout << "command " << command << " " << a << " " << b << "\n";
        
        if (command == 'U') {
            update(a, b, 1, 0, n);
        } else if (command == 'M') {
            cout << query_max(a, b, 1, 0, n) << "\n";
        } else if (command == 'S') {
            cout << query_sum(a, b, 1, 0, n) << "\n";
        } else if (command == 'I') {
            pair<LL,LL> tmp = query_increasing(a, b, 1, 0, n);
            if (tmp.first == -1 && tmp.second == -1) {
                cout << 0 << "\n";
            } else {
                // cout << tmp.first << " f " << tmp.second << " s\n";
                cout << 1 << "\n";
            }
        } else if (command == 'D') {
            pair<LL,LL> tmp =  query_decresing(a, b, 1, 0, n);
            if (tmp.first == -1 && tmp.second == -1) {
                cout << 0 << "\n";
            } else {
                cout << 1 << "\n";
            }
        }
    }
    return 0;
}