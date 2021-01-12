/*
JOI 2020 Power Plant
- We basically want to pick some power stations so that their spanning tree
  has them as leaves and (no. of leaves) - (no. of stations on spanning tree)
  is maximized
- Let dp[i] = Answer for i's subtree if any path (i -> c : c in i's subtree)
              visits at most one chosen node
            = max(S[i], sum(dp[c] : c in i's children) - S[i])
- Let mx[i] = max(dp[c] : c in i's children)
- Ans = max(max(mx[i] + S[i], dp[i]) : 1 <= 1 <= N)
- We can calculate dp and mx using a DFS
- Complexity: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

string s;
vector<int> graph[200001];
int dp[200001], ans = 1;

void dfs(int node = 1, int parent = 0) {
    int mx = 0;
    for (int i : graph[node]) if (i != parent) {
        dfs(i, node);
        dp[node] += dp[i];
        mx = max(mx, dp[i]);
    }
    dp[node] = max(s[node - 1] - '0', dp[node] - s[node - 1] + '0');
    ans = max(ans, max(mx + s[node - 1] - '0', dp[node]));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    cin >> s;
    dfs();
    cout << ans << '\n';
    return 0;
}