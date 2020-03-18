/*
- It's optimal to fill a stove to its maximum capacity if we put any stones in it
- So we place V stones in (S - 1) / V stoves and (S - 1) % V + 1 stones in 1 stove
- Do DP to calculate the result quickly
- Complexity: O(N^2)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[1001], dp[1001][1001][2][3];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, s, v;
    cin >> n >> s >> v;
    FOR(i, 1, n) cin >> a[i];

    if (s <= n / 2 * v) return cout << 0, 0;

    ll to_fill = (s - 1) / v, rem = (s - 1) % v + 1;
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0][0] = dp[0][1][0][1] = dp[0][0][1][2] = 0;

    FOR(i, 1, n) FOR(j, 0, to_fill + 1) {
        dp[i][j][0][0] = *min_element(dp[i - 1][j][0], dp[i - 1][j][0] + 3);
        dp[i][j][1][0] = *min_element(dp[i - 1][j][1], dp[i - 1][j][1] + 3);

        if (j) {
            dp[i][j][0][1] = min(dp[i - 1][j - 1][0][0], dp[i - 1][j - 1][0][1] + a[i] * v * v);
            dp[i][j][1][1] = min(dp[i - 1][j - 1][1][0], min(dp[i - 1][j - 1][1][1] + a[i] * v * v, dp[i - 1][j - 1][1][2] + a[i] * rem * v));
        }

        dp[i][j][1][2] = min(dp[i - 1][j][0][0], dp[i - 1][j][0][1] + a[i] * rem * v);
    }

    cout << *min_element(dp[n - 1][to_fill][1], dp[n - 1][to_fill][1] + 3) << '\n';
    return 0;
}