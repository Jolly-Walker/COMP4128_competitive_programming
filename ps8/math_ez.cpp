#include<bits/stdc++.h>
using namespace std;

#define maxn 100010


bool isprime(int x) {
    if(x < 2) return false;
    for(int f = 2; f*f<= x; f ++) {
        if(x % f == 0) return false;
    }
    return true;
}

bool ispow2(int x) {
    return (x & (x-1)) == 0;
}
// Returns prime factors in increasing order with right multiplicity.
vector<int> primefactorise(int x) {
    vector<int> factors;
    for(int f = 2; f*f <= x; f++) {
        while(x % f == 0) {
            factors.push_back(f);
            x /= f;
        }
    }
    if(x != 1) factors.push_back(x);
    return factors;
}

int main() {
    int tofactorise;
    cin >> tofactorise;
    map<int,int> counter;
    vector<int> primes = primefactorise(tofactorise);

    for(vector<int>::iterator it = primes.begin(); it != primes.end(); ++it) {
        counter[*it]++;
    }
    int min_val = 1;
    int max_power = 0;
    bool same = true;
    int prev = -1;
    for(map<int,int>::iterator it = counter.begin(); it != counter.end(); ++it) {
        //cout << it->first << "^" << it->second << "\n";
        min_val *= it->first;
        max_power = max(max_power, it->second);
        if (prev == -1) prev = it->second;
        if (prev != it->second) same = false;
    }
    int tmp = 1;
    int tmp_power = 0;

    while(tmp < max_power) {
        tmp = tmp *2;
        ++tmp_power;
    }
    //cout << tmp_power << "\n";
    // bool all_same = true;

    if (same and ispow2(max_power)) {
        cout << min_val << " " << tmp_power << "\n";//<< " steps\n";
    } else {
        cout << min_val << " " << tmp_power + 1 << "\n";// << " steps\n";
    }
    return 0;

}