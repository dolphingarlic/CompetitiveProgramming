#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<pair<int, int>> graph[2001];
int lucky[2001], visited[2001][2001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b, k;
    cin >> n >> m >> a >> b;
    FOR(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    cin >> k;
    FOR(i, 0, k) cin >> lucky[i];

    priority_queue<tuple<int, int, int>> pq;
    FOR(i, 0, k - 1) pq.push({-1, a, i});
    while (pq.size()) {
        int cost, curr, edge;
        tie(cost, curr, edge) = pq.top();
        pq.pop();
        if (visited[curr][edge]) continue;

        visited[curr][edge] = -cost;
        for (pair<int, int> i : graph[curr])
            if ((curr != lucky[edge] || i.first != lucky[edge + 1]) && (curr != lucky[edge + 1] || i.first != lucky[edge]))
                pq.push({cost - i.second, i.first, edge});
    }
    
    FOR(i, 0, k - 1) cout << visited[b][i] - 1 << '\n';
    return 0;
}