#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int dp[502][502];  // Min additions to get "jazz" from index i to j
                       // Inclusive and 0-indexed
    FOR(i, 0, 502) {
        fill(dp[i], dp[i] + 502, 0);
    }
    FOR(j, 0, s.size() + 1) {
        FOR(i, 0, s.size() - j) {
            dp[i][i + j] = dp[i + 1][i + j] + 1;
            FOR(k, i + 1, i + j + 1) {
                if (s[k] == s[i]) {
                    dp[i][i + j] =
                        min(dp[i][i + j], dp[i + 1][k - 1] + dp[k + 1][i + j]);
                }
            }
        }
    }
    cout << dp[0][s.size() - 1] << '\n';
    return 0;
}