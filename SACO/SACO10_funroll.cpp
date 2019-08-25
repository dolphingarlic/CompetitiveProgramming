#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll dp[4001][4001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    FOR(i, 0, 2 * n + 1) fill(dp[i], dp[i] + 2 * n + 1, 0);
    dp[0][0] = 1;
    FOR(i, 1, 2 * n + 1) {
        dp[i][0] = dp[i - 1][1];
        FOR(j, 1, i) dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j + 1]) % 4993;
        dp[i][i] = 1;
    }
    ll sum = 0;
    FOR(i, 0, n + 1) sum = (sum + dp[n][i]) % 4993;
    cout << (dp[2 * n][0] - sum + 4993) % 4993 << '\n';
    return 0;
}