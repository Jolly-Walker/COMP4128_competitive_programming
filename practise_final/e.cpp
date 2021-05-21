// https://github.com/MathIsLife/CoolestCodeLibrary/blob/master/CEOI%202004%20-%20Two%20Sawmills.cpp
/*
     |\   |  `|` |``\  ```|` |   |  /```\  |``\
     | \  |   |  |__/     |  |___| |     | |__/
     |  \ |   |  |  \     |  |   | |     | |  \
    _|   \|  _|_ |   \ \__)  |   |  \___/  |   \
    
        Central European Olympiad in Informatics 2004 - Two Sawmills
        
        Category: Data Structures
        
        Keys: Algebraic Manipulation, Convex Hull Trick
        
*/

#include <vector>
#include <cstdio>
 
using namespace std;

const int N = 2e4 + 10;

int n;
long long a[N];
long long total;
long long w[N], d[N];
vector <long long> m;
vector <long long> c;
int size, pointer;

bool bad (int l1, int l2, int l3) {
    return (c[l2] - c[l1]) * (m[l1] - m[l3]) >= (c[l3] - c[l1]) * (m[l1] - m[l2]);
}

void add (long long m0, long long c0) {
    ++size;
    m.push_back(m0);
    c.push_back(c0);
    while (size >= 3 and bad(size - 3, size - 2, size - 1)) {
	--size;
	m.erase(m.end() - 2);
	c.erase(c.end() - 2);
    }
}

long long query (long long x) {
    if (pointer >= size) pointer = size - 1;
    while (pointer < size - 1 and m[pointer] * x + c[pointer] < m[pointer + 1] * x + c[pointer + 1]) {
	++pointer;
    }
    return m[pointer] * x + c[pointer];
}

int main (int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
	scanf("%lld %lld", w + i, d + i + 1);
	total -= w[i] * d[i];
	w[i] += w[i - 1], d[i + 1] += d[i];
    }
    total += d[n + 1] * w[n];
    add(w[1], 0);
    long long ans = 0LL;
    for (int i = 2; i <= n; ++i) {
	ans = max(ans, query(d[i]) + w[i] * (d[n + 1] - d[i]));
	add(w[i], -w[i] * d[i]);
    }
    printf("%lld\n", total - ans);
    return 0;
}

