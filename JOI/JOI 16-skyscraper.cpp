/*
JOIOC 2016 Skyscrapers
- Connected component DP
- dp[i][j][k][m] = No. of ways to insert first i buildings into permutation with
                   j connected components, total cost k, and m ends of permutation inserted
- At dp[i], we assume that the unfilled elements are all a[i + 1], where a[n + 1] = inf
- Let cost_diff be the change in cost when we transition from dp[i - 1] to dp[i]
    - cost_diff = (2 * j - m) * (a[i + 1] - a[i])
- There are 5 cases:
    - Case 1: we insert a[i] to form a new component that isn't an end of the permutation
    - Case 2: we insert a[i] to form a new component that is an end of the permutation
    - Case 3: we append a[i] to an existing component such that a[i] isn't an end of the permutation
    - Case 4: we append a[i] to an existing component such taht a[i] is an end of the permutation
    - Case 5: we insert a[i] to join two existing components
- See the code for more details on how to handle the cases
- Complexity: O(N^2 L)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

int a[102];
ll dp[102][102][1002][3];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, l;
    cin >> n >> l;
    if (n == 1) return cout << 1, 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    a[n + 1] = 10000;
    dp[0][0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            for (int k = 0; k <= l; k++) {
                for (int m = 0; m <= 2; m++) {
                    int cost_diff = (2 * j - m) * (a[i + 1] - a[i]);
                    if (cost_diff > k || i + j + 1 - m > n) continue;

                    // Case 1
                    dp[i][j][k][m] += dp[i - 1][j - 1][k - cost_diff][m];
                    // Case 2
                    if (m) dp[i][j][k][m] += (3 - m) * dp[i - 1][j - 1][k - cost_diff][m - 1];
                    // Case 3
                    dp[i][j][k][m] += (2 * j - m) * dp[i - 1][j][k - cost_diff][m];
                    // Case 4
                    if (m == 1) dp[i][j][k][m] += 2 * j * dp[i - 1][j][k - cost_diff][m - 1];
                    if (m == 2) {
                        if (i == n) dp[i][j][k][m] += dp[i - 1][j][k - cost_diff][m - 1];
                        else if (j > 1) dp[i][j][k][m] += (j - 1) * dp[i - 1][j][k - cost_diff][m - 1];
                    }
                    // Case 5
                    if (m == 2) {
                        if (i == n) dp[i][j][k][m] += dp[i - 1][j + 1][k - cost_diff][m];
                        else dp[i][j][k][m] += j * (j - 1) * dp[i - 1][j + 1][k - cost_diff][m];
                    } else if (m == 1) dp[i][j][k][m] += j * j * dp[i - 1][j + 1][k - cost_diff][m]; 
                    else dp[i][j][k][m] += j * (j + 1) * dp[i - 1][j + 1][k - cost_diff][m];

                    dp[i][j][k][m] %= MOD;
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i <= l; i++) ans += dp[n][1][i][2];
    cout << ans % MOD;
    return 0;
}