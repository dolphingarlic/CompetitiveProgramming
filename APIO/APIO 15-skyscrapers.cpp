#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

set<int> doges[30000];
vector<pair<int, int>> graph[30000];
int visited[30000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, src, dest;
    cin >> n >> m;
    FOR(i, 0, m) {
        int b, p;
        cin >> b >> p;
        if (!i) src = b;
        if (i == 1) dest = b;
        doges[b].insert(p);
    }

    FOR(i, 0, n) {
        for (int j : doges[i]) {
            for (int k = i + j, cnt = 1; k < n; k += j, cnt++) {
                graph[i].push_back({k, cnt});
                if (doges[k].find(j) != doges[k].end()) break;
            }
            for (int k = i - j, cnt = 1; k >= 0; k -= j, cnt++) {
                graph[i].push_back({k, cnt});
                if (doges[k].find(j) != doges[k].end()) break;
            }
        }
    }

    memset(visited, 0x3f, sizeof visited);
    priority_queue<pair<int, int>> pq;
    pq.push({0, src});
    visited[src] = 0;
    while (pq.size()) {
        int dist, node;
        tie(dist, node) = pq.top();
        pq.pop();
        if (node == dest) return cout << -dist, 0;
        for (pair<int, int> i : graph[node]) {
            if (i.second - dist < visited[i.first]) {
                visited[i.first] = i.second - dist;
                pq.push({dist - i.second, i.first});
            }
        }
    }
    cout << -1;
    return 0;
}