#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> edge; //(distance, vertex )
typedef pair<int, edge> queue_node;
int my_graph[1005][1005];
int seen[1005][1005];
int dist[1005][1005];
priority_queue<queue_node, vector<queue_node>,greater<queue_node>> pq;

void dikstras(int num_lines, int num_cols) {
        // put the source s in the queue
        pq.push(make_pair(my_graph[1][1], make_pair(1,1)));
        // cout << pq.top().first << "\n";
        int min_ans = 0x7FFFFFFF;
        while (!pq.empty()) {
            // choose(d,v) so that d is minimal, 
            // i.e.the closest unvisited vertex
            pair<int,edge> cur = pq.top();
            pq.pop();
            edge v = cur.second;
            int d = cur.first;
            if (v.first == num_lines && v.second == num_cols) {
                //cout << d << "\n";
                min_ans = min(min_ans, d);
            }
            if (seen[v.first][v.second]) {
                continue;
            }

            dist[v.first][v.second] = d;
            seen[v.first][v.second] = true;
            // relax all edges from v
            // just look at right or down
            if (v.first < num_lines) {
                edge next = v;
                ++next.first;
                int weight = my_graph[next.first][next.second];
                if(!seen[next.first][next.second]) {
                    pq.push(make_pair(d + weight, next));
                }
            }
            if (v.second < num_cols) {
                edge next = v;
                ++next.second;
                int weight = my_graph[next.first][next.second];
                if(!seen[next.first][next.second]) {
                    pq.push(make_pair(d + weight, next));
                }
            }

            // nevermind you can still go up and left
            if (v.first > 1) {
                edge next = v;
                --next.first;
                int weight = my_graph[next.first][next.second];
                if(!seen[next.first][next.second]) {
                    pq.push(make_pair(d + weight, next));
                }
            }

            if (v.second > 1) {
                edge next = v;
                --next.second;
                int weight = my_graph[next.first][next.second];
                if(!seen[next.first][next.second]) {
                    pq.push(make_pair(d + weight, next));
                }
            }
        }
        //cout << "min ans: " << min_ans << "\n";
        cout << min_ans << "\n";
        return;
}

int main() {
    int num_maze;
    cin >> num_maze;

    for (int ff = 0; ff < num_maze; ++ff) {
        int num_lines, num_cols;
        cin >> num_lines >> num_cols;

        //clear graph
        for (int i = 1; i <= 1000; ++i) {
            for (int j = 1; j <= 1000; ++j) {
                my_graph[i][j] = 0;
                seen[i][j] = false;
            }
        }
        // read in the graph
        for (int i = 1; i <= num_lines; ++i) {
            for (int j = 1; j <= num_cols; ++j) {
                cin >> my_graph[i][j];
            }
        }
        dikstras(num_lines, num_cols);
        //cout << dikstras(num_lines, num_cols) << "\n";
    }
    return 0;
}