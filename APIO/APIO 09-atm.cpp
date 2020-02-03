#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[500001], reversed[500001], stck;
bool is_pub[500001], visited[500001], has_pub[500001];
int w[500001], scc_w[500001], cmp[500001], scc = 1, dp[500001];
set<int> conn[500001];

void dfs1(int node) {
    visited[node] = true;
    for (int i : graph[node])
        if (!visited[i]) dfs1(i);
    stck.push_back(node);
}

void dfs2(int node) {
    cmp[node] = scc;
    has_pub[scc] |= is_pub[node];
    scc_w[scc] += w[node];
    for (int i : reversed[node]) {
        if (!cmp[i])
            dfs2(i);
        else if (cmp[i] != scc)
            conn[scc].insert(cmp[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, m) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    FOR(i, 1, n + 1) cin >> w[i];

    int s, p;
    cin >> s >> p;
    FOR(i, 0, p) {
        int x;
        cin >> x;
        is_pub[x] = true;
    }

    FOR(i, 1, n + 1) if (!visited[i]) dfs1(i);
    FOR(i, 1, n + 1) for (int j : graph[i]) reversed[j].push_back(i);
    while (stck.size()) {
        if (!cmp[stck.back()]) {
            dfs2(stck.back());
            scc++;
        }
        stck.pop_back();
    }

    for (int i = scc - 1; i; i--) {
        if (dp[i]) {
            for (int j : conn[i]) dp[j] = max(dp[j], scc_w[j] + dp[i]);
        } else if (has_pub[i]) {
            dp[i] = scc_w[i];
            for (int j : conn[i]) dp[j] = max(dp[j], scc_w[j] + dp[i]);
        }
    }

    cout << dp[cmp[s]];

    return 0;
}
