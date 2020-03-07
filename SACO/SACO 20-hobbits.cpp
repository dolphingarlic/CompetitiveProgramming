#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dp(m + 1);
    FOR(i, 0, m + 1) dp[i].resize(n + 1);
    FOR(i, 1, m + 1) FOR(j, 1, n + 1) {
        char c;
        cin >> c;
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + (c == 'X');
    }
    cout << dp[m][n];
    return 0;
}