/*
SACO 2021 Maximum Subtree
- All-roots tree DP
- Complexity: O(N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool c[100001];
vector<int> graph[100001];
int dp[100001], ans[100001];

void dfs1(int node = 1, int parent = 0) {
    dp[node] = -1 + 2 * c[node];
    for (int i : graph[node]) if (i != parent) {
        dfs1(i, node);
        dp[node] += max(0, dp[i]);
    }
}

void dfs2(int node = 1, int parent = 0, int par_dp = 0) {
    ans[node] = dp[node] + par_dp;
    for (int i : graph[node]) if (i != parent)
        dfs2(i, node, max(0, par_dp + dp[node] - max(0, dp[i])));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs1();
    dfs2();
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    return 0;
}
