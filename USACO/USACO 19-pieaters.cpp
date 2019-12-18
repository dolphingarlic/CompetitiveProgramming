#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll dp[302][302], weight[302][302], pref[302][302][302];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, m) {
        ll w, a, b;
        cin >> w >> a >> b;
        weight[a][b] = w;
        FOR(j, a, b + 1) pref[a][j][b] = w;
    }

    FOR(k, 1, n + 1) {
        FOR(i, 1, n - k + 2) {
            FOR(j, i + 1, i + k) pref[i][j][i + k - 1] = max(pref[i][j][i + k - 1], pref[i + 1][j][i + k - 1]);
            FOR(j, i, i + k - 1) pref[i][j][i + k - 1] = max(pref[i][j][i + k - 1], pref[i][j][i + k - 2]);
        }
    }

    FOR(k, 1, n + 1) {
        FOR(i, 1, n - k + 2) {
            FOR(j, i, i + k) {
                dp[i][i + k] = max(dp[i][i + k], dp[i][j] + dp[j + 1][i + k] + pref[i][j][i + k - 1]);
            }
        }
    }

    cout << dp[1][n + 1];
    return 0;
}
