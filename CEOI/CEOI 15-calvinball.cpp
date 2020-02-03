#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;
typedef long long ll;

const ll MOD = 1e6 + 7;

ll a[10001], mx[10001], dp[2][10001];

int main() {
    int n;
    cin >> n;
    FOR(i, 0, n) {
        dp[0][i] = 1;
        cin >> a[i];
        if (i) mx[i] = max(mx[i - 1], a[i - 1]);
    }

    ll ans = 1;
    for (int i = n - 1; ~i; i--) {
        ans = (ans + ((a[i] - 1) * dp[0][mx[i]]) % MOD) % MOD;

        FOR(j, 0, i)
        dp[1][j] = (j * dp[0][j] + dp[0][j + 1]) % MOD;
        FOR(j, 0, n + 1) dp[0][j] = dp[1][j];
    }

    cout << ans;
    return 0;
}
