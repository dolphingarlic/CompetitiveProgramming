/*
PAIO 2020 Rocket Shipyard
- dp[i][j] = Minimum number of mistakes for i engineers and j tasks
           = 0 if (i, j) is effective
             min(i * j, dp[k][j] + dp[i-k][j], dp[i][l] + dp[i][j-l]) otherwise
- Complexity: O(NM(N + M))
*/

#include <bits/stdc++.h>
using namespace std;

int dp[501][501];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) dp[i][j] = i * j;
    while (k--) {
        int e, t;
        cin >> e >> t;
        dp[e][t] = 0;
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        for (int t = 1; t < i; t++) dp[i][j] = min(dp[i][j], dp[t][j] + dp[i - t][j]);
        for (int t = 1; t < j; t++) dp[i][j] = min(dp[i][j], dp[i][t] + dp[i][j - t]);
    }
    cout << dp[n][m] << '\n';
    return 0;
}