#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int dp[101][101], ans = 0;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        FOR(j, 1, i + 1) {
            int x;
            cin >> x;
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + x;
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans << '\n';
    return 0;
}