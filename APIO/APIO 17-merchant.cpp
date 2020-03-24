#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll INF = LLONG_MAX / 2;

int n, m, x;
ll b[101][1001], s[101][1001];
ll graph[101][101], profit[101][101], graph2[101][101];

void floyd_warshall(ll adj[101][101]) {
    FOR(i, 1, n + 1)
        FOR(j, 1, n + 1)
            FOR(k, 1, n + 1)
                adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> x;
    FOR(i, 1, n + 1) {
        FOR(j, 1, n + 1) graph[i][j] = INF;
        FOR(j, 1, x + 1) cin >> b[i][j] >> s[i][j];
    }
    FOR(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
    }
    floyd_warshall(graph);
    FOR(i, 1, n + 1) FOR(j, 1, n + 1) FOR(k, 1, x + 1) 
        if (s[j][k] != -1 && b[i][k] != -1)
            profit[i][j] = max(profit[i][j], s[j][k] - b[i][k]);

    ll l = 1, r = 1e9;
    while (l <= r) {
        ll mid = (l + r) / 2;
        FOR(i, 1, n + 1) FOR(j, 1, n + 1)
            graph2[i][j] = mid * min(graph[i][j], INF / mid) - profit[i][j];
        floyd_warshall(graph2);
        bool has_nonnegative_cycle = false;
        FOR(i, 1, n + 1) if (graph2[i][i] <= 0) has_nonnegative_cycle = true;
        if (has_nonnegative_cycle) l = mid + 1;
        else r = mid - 1;
    }
    cout << r;
    return 0;
}