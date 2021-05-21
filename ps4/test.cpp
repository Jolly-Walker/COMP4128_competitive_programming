#include<bits/stdc++.h>
int main() {
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> q2;
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q2.push(std::make_pair(n,n+1));
    
    int k = 10;
    while(k) {
        std::cout << q2.top().first << " " << q2.top().second << " \n";
        q2.pop();
        --k;
    }
    return 0;
}