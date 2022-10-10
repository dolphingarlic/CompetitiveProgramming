#include <iostream>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

int b[100];
ll dp[100][1001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    if (n == 1) return cout << b[0] + 1, 0;
    if (n == 2) return cout << (b[0] < b[1] ? b[0] : b[1]) + 1, 0;

    for (int i = 0; i <= b[0]; i++) dp[0][i] = 1;
    ll ans = 0;
    for (int shift = 0; shift <= b[0]; shift++) {
        for (int i = 1; i < n - 1; i++) {
            fill_n(dp[i], b[i] + 1, 0);
            for (int j = 0; j <= b[i] - shift; j++) {
                for (int k = 0; k <= b[i] - shift - j; k++) {
                    dp[i][j] += dp[i - 1][k];
                    if (dp[i][j] >= MOD) dp[i][j] -= MOD;
                }
            }
        }
        for (int i = 0; i <= b[n - 1] - shift; i++) {
            ans += dp[n - 2][i];
            if (ans >= MOD) ans -= MOD;
        }
        dp[0][b[0] - shift] = 0;
    }
    cout << ans;
    return 0;
}
