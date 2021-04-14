#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7, INV = 5e8 + 4;

ll a[3001], dp[3001][3001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) dp[i][j] = a[i] > a[j];

    for (int _ = 1; _ <= q; _++) {
        int x, y;
        cin >> x >> y;
        for (int i = 1; i <= n; i++)
            if (i != x && i != y) {
                ll xi = (dp[x][i] + dp[y][i]) * INV % MOD;
                ll ix = (dp[i][x] + dp[i][y]) * INV % MOD;
                dp[x][i] = dp[y][i] = xi;
                dp[i][x] = dp[i][y] = ix;
            }
        dp[x][y] = dp[y][x] = (dp[x][y] + dp[y][x]) * INV % MOD;
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            ans += dp[i][j];
            if (ans >= MOD) ans -= MOD;
        }
    for (int i = 1; i <= q; i++) ans = ans * 2 % MOD;
    cout << ans;
    return 0;
}
