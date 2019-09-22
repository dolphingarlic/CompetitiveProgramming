#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

pair<int, int> a[251];

ll graph[1000][1000], r_graph[1000][1000], parent[1000];
bool visited[1000];

bool bfs(int s, int t, int n) {
    fill(visited, visited + n, false);

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (q.size()) {
        int curr = q.front();
        q.pop();
        FOR(i, 0, n) {
            if (!visited[i] && r_graph[curr][i]) {
                q.push(i);
                parent[i] = curr;
                visited[i] = true;
            }
        }
    }

    return visited[t];
}

ll max_flow(int s, int t, int n) {
    FOR(i, 0, n) FOR(j, 0, n) r_graph[i][j] = graph[i][j];

    ll max_flow = 0;

    while (bfs(s, t, n)) {
        ll path_flow = INT_MAX;
        for (int i = t; i != s; i = parent[i]) {
            int j = parent[i];
            path_flow = min(path_flow, r_graph[j][i]);
        }
        for (int i = t; i != s; i = parent[i]) {
            int j = parent[i];
            r_graph[j][i] -= path_flow;
            r_graph[i][j] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int l, w, n;
    cin >> l >> w >> n;
    FOR(i, 1, n + 1) {
        cin >> a[i].first >> a[i].second;
    }

    FOR(i, 1, n + 1) {
        graph[2 * i][2 * i + 1] = 1;

        if (a[i].second - 100 <= 0)
            graph[0][2 * i] = INT_MAX;
        if (a[i].second + 100 >= w)
            graph[2 * i + 1][2 * n + 2] = INT_MAX;
        FOR(j, i + 1, n + 1) {
            if ((a[i].first - a[j].first) * (a[i].first - a[j].first) + (a[i].second - a[j].second) * (a[i].second - a[j].second) <= 40000) {
                graph[2 * i + 1][2 * j] = INT_MAX;
                graph[2 * j + 1][2 * i] = INT_MAX;
            }
        }
    }

    cout << max_flow(0, 2 * n + 2, 2 * n + 3);
    return 0;
}