#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int c, t, f, ans = INT_MAX;
vector<int> graph[5001];
int min_dist[9][5001];
bool visited[9];

void dfs(int node = 0, int len = 0, int depth = 0) {
    visited[node] = true;
    if (depth == t) ans = min(ans, len + min_dist[node][0]);
    else {
        FOR(i, 1, t + 1) {
            if (!visited[i]) dfs(i, len + min_dist[node][i], depth + 1);
        }
    }
    visited[node] = false;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> c >> t >> f;

    FOR(i, 0, f) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    FOR(i, 0, t + 1) {
        queue<int> q;
        q.push(i);
        min_dist[i][i] = 1;
        while (!q.size()) {
            int curr = q.front();
            q.pop();
            for (int j : graph[curr]) {
                if (!min_dist[i][j]) {
                    min_dist[i][j] = min_dist[i][curr] + 1;
                    q.push(j);
                }
            }
        }
        FOR(j, 0, c) min_dist[i][j]--;
    }

    dfs();

    cout << ans;
    return 0;
}