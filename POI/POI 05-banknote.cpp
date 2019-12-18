/*
POI 2005 Banknote
- This is basically just the coin change problem but with limited coins
- The same approach as before works, but we just have to check that a given
  configuration doesn't exceed any limits
- To do that we can keep a count of how much each note is used for all configurations
- Complexity: O(NK)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int b[200], c[200], dp[20001][200], dp_cnt[20001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n;
    FOR(i, 0, n) cin >> b[i];
    FOR(i, 0, n) cin >> c[i];
    cin >> k;

    FOR(i, 1, k + 1) {
        fill(dp[i], dp[i] + n, 40000);
        dp_cnt[i] = INT_MAX;
        int best = -1;

        FOR(j, 0, n) {
            if (i - b[j] < 0 || dp[i - b[j]][j] >= c[j]) continue;
            if (dp_cnt[i - b[j]] < dp_cnt[i]) {
                dp_cnt[i] = dp_cnt[i - b[j]] + 1;
                best = j;
            }
        }

        if (~best) {
            FOR(j, 0, n) {
                dp[i][j] = dp[i - b[best]][j];
                if (j == best) dp[i][j]++;
            }
        }
    }

    cout << dp_cnt[k] << '\n';
    FOR(i, 0, n) cout << dp[k][i] << ' ';
    return 0;
}