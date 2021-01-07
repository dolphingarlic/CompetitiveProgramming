#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll choose[301][301], dp[301][301];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) for (int j = 0; j <= i; j++) {
        if (!j || j == i) choose[i][j] = 1;
        else choose[i][j] = (choose[i - 1][j] + choose[i - 1][j - 1]) % MOD;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= m; i++) for (int j = i; j <= n; j++) {
        for (int k = 1; k <= j - i + 1; k++)
            dp[i][j] = (dp[i][j] + choose[j][k] * dp[i - 1][j - k]) % MOD;
        cout << i << ' ' << j << ' ' << dp[i][j] << '\n';
    }
    cout << dp[m][n];
    return 0;
}