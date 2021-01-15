#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int dp[501][501];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, max(m, n) + 1) {
        dp[i][i] = 0;
        FOR(j, 1, max(m, n) + 1) {
            if (i == j) continue;
            dp[i][j] = INT_MAX;
            FOR(k, 1, j) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
            }
            FOR(k, 1, i) {
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
            }
        }
    }
    cout << dp[n][m] << '\n';
    return 0;
}