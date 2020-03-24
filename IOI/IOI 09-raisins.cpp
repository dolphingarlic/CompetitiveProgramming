#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int dp[51][51][51][51], a[51][51], pref[51][51];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        cin >> a[i][j];
        pref[i][j] = pref[i - 1][j] + pref[i][j - 1] + a[i][j] - pref[i - 1][j - 1];
    }

    FOR(i, 1, n + 1) FOR(j, 1, m + 1) FOR(k, 1, n - i + 2) FOR(l, 1, m - j + 2) {
        if (i == 1 && j == 1) continue;
        int mn = INT_MAX;
        FOR(x, 1, i) mn = min(mn, dp[k][l][x][j] + dp[k + x][l][i - x][j]);
        FOR(x, 1, j) mn = min(mn, dp[k][l][i][x] + dp[k][l + x][i][j - x]);
        dp[k][l][i][j] = mn + pref[k + i - 1][l + j - 1] + pref[k - 1][l - 1] - pref[k + i - 1][l - 1] - pref[k - 1][l + j - 1];
    }

    cout << dp[1][1][n][m];
    return 0;
}