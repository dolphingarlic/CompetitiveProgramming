/*
NOI.cn 2009 Modified Treap
- First, sort the nodes by their keys
- Let dp[l][r][w] = Min cost to construct a BST with the nodes [l, r]
                    such that the root's priority is at least w
                  = min(
                      { dp[l][m - 1][w] + dp[m + 1][r][w] + k : m from l to r },
                      { dp[l][m - 1][p[m]] + dp[m + 1][r][p[m]] : m from l to r and p[m] >= w }
                    ) + (Sum of frequencies of nodes [l, r])
- Using memoization, this runs in O(N^4) time because w in our DP array
  can only take on O(N) values (kinda like coordinate compression)
- The first case of our DP transition is from changing the priority of node m
- The second case of our DP transition is from not changing the priority
  because we don't have to
    - Note that we still need the other case because it may not be optimal not
      to change the priority even if we don't have to
- Complexity: O(N^4)
*/

#include <bits/stdc++.h>
using namespace std;

int n;
array<int, 3> node[71];
int k, pref[71];
unordered_map<int, int> dp[71][71];

int solve(int l, int r, int mn) {
    if (l > r) return 0;
    if (l == r) return k * (node[l][1] < mn) + node[l][2];
    if (dp[l][r].count(mn)) return dp[l][r][mn];
    int ans = INT_MAX;
    for (int i = l; i <= r; i++) {
        ans = min(ans, solve(l, i - 1, mn) + solve(i + 1, r, mn) + k);
        if (node[i][1] >= mn)
            ans = min(ans, solve(l, i - 1, node[i][1]) + solve(i + 1, r, node[i][1]));
    }
    return dp[l][r][mn] = ans + pref[r] - pref[l - 1];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    for (int i : {0, 1, 2})
        for (int j = 1; j <= n; j++) cin >> node[j][i];
    sort(node + 1, node + n + 1);
    for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + node[i][2];
    cout << solve(1, n, 0);
    return 0;
}
