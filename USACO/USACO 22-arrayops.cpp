#include <iostream>
#include <numeric>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, mn = 1000, b[100];
    ll dp[100][1001];
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        mn = min(mn, b[i]);
    }
    if (n == 1) return cout << b[0] + 1, 0;
    if (n == 2) return cout << min(b[0], b[1]) + 1, 0;
    ll ans = 0;
    for (int shift = 0; shift <= mn; shift++) {
        iota(dp[0], dp[0] + b[0] + 1 - shift, 1);
        for (int j = b[0] - shift + 1; j <= 1000; j++) dp[0][j] = dp[0][j - 1];
        for (int i = 1; i < n - 1; i++) {
            for (int j = 0; j <= b[i] - shift; j++) {
                if (j) dp[i][j] = dp[i][j - 1] + dp[i - 1][b[i] - shift - j];
                else dp[i][j] = dp[i - 1][b[i] - shift - j];
                if (dp[i][j] >= MOD) dp[i][j] -= MOD;
            }
            for (int j = b[i] - shift + 1; j <= 1000; j++) dp[i][j] = dp[i][j - 1];
        }
        ans += dp[n - 2][b[n - 1] - shift];
        if (ans >= MOD) ans -= MOD;
    }
    cout << ans;
    return 0;
}
