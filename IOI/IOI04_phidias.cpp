#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int dp[601][601];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int W, H;
    cin >> W >> H;
    FOR(i, 0, W + 1) FOR(j, 0, H + 1) dp[i][j] = i * j;
    int n;
    cin >> n;
    FOR(i, 0, n) {
        int a, b;
        cin >> a >> b;
        dp[a][b] = 0;
    }

    FOR(i, 1, W + 1) {
        FOR(j, 1, H + 1) {
            // Fixed height
            FOR(k, 1, i) dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j]);
            //Fixed width
            FOR(k, 1, j) dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k]);

            // cout << dp[i][j] << '\t';
        }
        // cout << '\n';
    }

    cout << dp[W][H] << '\n';
    return 0;
}