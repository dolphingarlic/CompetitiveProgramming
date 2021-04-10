/*
USACO 2021 Balanced Subsets
- If we view a balanced subset as a list of subarrays, then we can notice
  that the left and right endpoints of the subarrays are unimodal (i.e. the
  subarrays extend left and then right on the left side, etc.)
- This means that we can use dynamic programming to solve this:
    dp[i][l][r][x][y] = Number of ways to get a balanced subset with [l, r]
                        as the lowest subarray in row i, and x and y are
                        boolean flags indicating whether the endpoints are
                        increasing or decreasing
    - See code for transitions
- Naively, this takes O(N^5) time to compute, but we can use prefix/suffix
  sums to speed this up to O(N^4)
- With a few constant factor optimizations, this passes in less than 2s
- (We can use 2D prefix sums to get it down to O(N^3), but the constant
  factor will be close to N so it won't make much of a difference)
*/

#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

string grid[151];
ll dp[151][151][151][2][2], pref[151][151][151][2][2], suff[151][151][2][2];
bool good[151][151][151];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> grid[i];
        for (int l = 1; l <= n; l++) {
            good[i][l][l] = (grid[i][l - 1] == 'G');
            dp[i][l][l][1][1] = good[i][l][l];
            for (int r = l + 1; r <= n && good[i][l][r - 1]; r++) {
                good[i][l][r] = (grid[i][r - 1] == 'G');
                dp[i][l][r][1][1] = good[i][l][r];
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int l = 1; l <= n; l++) for (int r = l; r <= n; r++) if (good[i][l][r]) {
            // dp[i][l][r][0][0]
            for (int pl = 1; pl < l; pl++) {
                dp[i][l][r][0][0] += pref[i - 1][pl][n][0][0] - pref[i - 1][pl][r][0][0] +
                                     pref[i - 1][pl][n][0][1] - pref[i - 1][pl][r][0][1] +
                                     pref[i - 1][pl][n][1][0] - pref[i - 1][pl][r][1][0] +
                                     pref[i - 1][pl][n][1][1] - pref[i - 1][pl][r][1][1];
            }
            dp[i][l][r][0][0] += suff[r][l - 1][1][0] - suff[r][0][1][0] +
                                 suff[r][l - 1][0][0] - suff[r][0][0][0] +
                                 pref[i - 1][l][n][0][1] - pref[i - 1][l][r][0][1] +
                                 pref[i - 1][l][n][0][0] - pref[i - 1][l][r][0][0] +
                                 dp[i - 1][l][r][0][0];
            dp[i][l][r][0][0] %= MOD;

            // dp[i][l][r][0][1]
            for (int pl = 1; pl < l; pl++) {
                dp[i][l][r][0][1] += pref[i - 1][pl][r][0][1] - pref[i - 1][pl][l - 1][0][1] +
                                     pref[i - 1][pl][r][1][1] - pref[i - 1][pl][l - 1][1][1];
            }
            dp[i][l][r][0][1] += pref[i - 1][l][r][0][1] - pref[i - 1][l][l - 1][0][1];
            dp[i][l][r][0][1] %= MOD;
            
            // dp[i][l][r][1][0]
            for (int pl = l; pl <= r; pl++) {
                dp[i][l][r][1][0] += pref[i - 1][pl][n][1][0] - pref[i - 1][pl][r][1][0] +
                                     pref[i - 1][pl][n][1][1] - pref[i - 1][pl][r][1][1];
            }
            dp[i][l][r][1][0] += suff[r][r][1][0] - suff[r][l - 1][1][0];
            dp[i][l][r][1][0] %= MOD;
            
            // dp[i][l][r][1][1]
            for (int pl = l; pl <= r; pl++) {
                dp[i][l][r][1][1] += pref[i - 1][pl][r][1][1] - pref[i - 1][pl][pl - 1][1][1];
            }
            dp[i][l][r][1][1] %= MOD;
        }

        for (int l = 1; l <= n; l++) for (int r = l; r <= n; r++) {
            for (int x : {0, 1}) for (int y : {0, 1})
                pref[i][l][r][x][y] = pref[i][l][r - 1][x][y] + dp[i][l][r][x][y] % MOD;
        }
        for (int r = 1; r <= n; r++) for (int l = 1; l <= r; l++) {
            for (int x : {0, 1}) for (int y : {0, 1})
                suff[r][l][x][y] = suff[r][l - 1][x][y] + dp[i][l][r][x][y] % MOD;
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) for (int l = 1; l <= n; l++) {
        ans += pref[i][l][n][0][0] + pref[i][l][n][0][1] + pref[i][l][n][1][0] + pref[i][l][n][1][1];
    }
    cout << ans % MOD;
    return 0;
}
