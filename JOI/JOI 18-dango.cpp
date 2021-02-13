/*
JOI 2018 Dango Maker
- Process cells by diagonals
- dp[i][j][k] = Max if we've processed up to cell (i, j) and k indicates the type
                of skewer **ending** on cell (i, j):
                - 0 if there is none
                - 1 if the skewer is horizontal
                - 2 if the skewer is vertical
- dp[i][j] depends only dp[i - 1][j + 1] and dp[i - 2][j + 2]
- The rest is casework; see code for details
- Complexity: O(NM)
*/

#include <bits/stdc++.h>
using namespace std;

string grid[3000];
int dp[3002][3002][3], prv = 0;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> grid[i];
    for (int diag = 2; diag <= n + m - 2; diag++) {
        for (int i = 0; i < n; i++) {
            int j = diag - i;
            if (j < 0 || j >= m) continue;
            dp[i][j][0] = prv;
            if (j > 1 && grid[i][j] == 'W' && grid[i][j - 1] == 'G' && grid[i][j - 2] == 'R')
                dp[i][j][1] = prv + 1;
            if (i > 1 && grid[i][j] == 'W' && grid[i - 1][j] == 'G' && grid[i - 2][j] == 'R') {
                if (j == m - 1) dp[i][j][2] = prv + 1;
                else if (j == m - 2) dp[i][j][2] = max(dp[i - 1][j + 1][2], dp[i - 1][j + 1][0]) + 1;
                else dp[i][j][2] = max({dp[i - 1][j + 1][2], dp[i - 2][j + 2][2], dp[i - 2][j + 2][0]}) + 1;
            }
            prv = *max_element(dp[i][j], dp[i][j] + 3);
        }
    }
    cout << prv;
    return 0;
}
