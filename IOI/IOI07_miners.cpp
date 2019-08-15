#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

int dp[2][4][4][4][4], food[100001];

inline int calc(int a, int b, int c) {
    return 1 + (c != b && b) + (c != a && b != a && a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    FOR(i, 1, n + 1) {
        char c;
        cin >> c;
        food[i] = (c == 'F' ? 1 : c == 'M' ? 2 : 3);
    }

    FOR(i, 0, 2) FOR(j, 0, 4) FOR(k, 0, 4) FOR(l, 0, 4) FOR(m, 0, 4) dp[i][j][k][l][m] = INT_MIN;
    dp[0][0][0][0][0] = 0;

    FOR(i, 1, n + 1) FOR(j, 0, 4) FOR(k, 0, 4) FOR(l, 0, 4) FOR(m, 0, 4) {
        dp[i % 2][k][food[i]][l][m] = max(dp[i % 2][k][food[i]][l][m], dp[(i - 1) % 2][j][k][l][m] + calc(j, k, food[i]));
        dp[i % 2][j][k][m][food[i]] = max(dp[i % 2][j][k][m][food[i]], dp[(i - 1) % 2][j][k][l][m] + calc(l, m, food[i]));
    }

    int ans = 0;
    FOR(j, 0, 4) FOR(k, 0, 4) FOR(l, 0, 4) FOR(m, 0, 4) {
        ans = max(ans, dp[(n & 1)][j][k][l][m]);
    }
    cout << ans << '\n';
    return 0;
}