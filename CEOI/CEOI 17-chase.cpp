/*
CEOI 2017 Chase
- Consider the case where Jerry ends on node 1
- We can do tree dp:
    dp[i][j] = Maximum difference if Jerry starts in i's subtree, sprinkles j crumbs, and ends on i
- If Jerry sprinkles a crumb at node i, he adds sum(p[c] : c in i's children) to the difference
- We can thus find each dp[i][j] in O(NK) time
- To handle other possible ending nodes, keep a second dp array storing the answer if Jerry
  **starts** on node i and goes into i's subtree instead
- Complexity: O(NK)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, k, p[100001];
vector<int> graph[100001];
ll dp1[100001][101], dp2[100001][101], ans = 0;

void dfs(int node = 1, int par = 0) {
    ll sm = 0;
    for (int i : graph[node]) sm += p[i];
    dp2[node][1] = sm;
    for (int i : graph[node]) if (i != par) {
        dfs(i, node);
        for (int j = 1; j <= k; j++) ans = max(ans, dp2[node][j] + dp1[i][k - j]);
        for (int j = 1; j <= k; j++) {
            dp1[node][j] = max({dp1[node][j], dp1[i][j], dp1[i][j - 1] + sm - p[par]});
            dp2[node][j] = max({dp2[node][j], dp2[i][j], dp2[i][j - 1] + sm - p[i]});
        }
    }
    fill(dp2[node] + 1, dp2[node] + k + 1, 0);
    dp2[node][1] = sm;
    reverse(graph[node].begin(), graph[node].end());
    for (int i : graph[node]) if (i != par) {
        for (int j = 1; j <= k; j++) ans = max(ans, dp2[node][j] + dp1[i][k - j]);
        for (int j = 1; j <= k; j++)
            dp2[node][j] = max({dp2[node][j], dp2[i][j], dp2[i][j - 1] + sm - p[i]});
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs();
    cout << ans;
    return 0;
}
