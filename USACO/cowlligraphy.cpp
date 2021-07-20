/*
Cowlligraphy
- Input: N, M, and the partially-filled grid
- Output: The maximum number of "moo"s and the filled grid
- Constraints: N <= 10 and M <= 100
- Complexity: O(NM * 3^N)
- Topics: Broken profile (bitmask) DP, Casework, Backtracking
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e5;

string grid[10];
int p3[11]{1}, prv[59049], dp[10][100][59049], backtrack[10][100][59049];

inline int get(int mask, int pos) { return mask / p3[pos] % 3; }

inline bool is(int i, int j, char c) { return grid[i][j] == c || grid[i][j] == '?'; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> grid[i];

    for (int i = 1; i <= n; i++) p3[i] = 3 * p3[i - 1];
    for (int mask = 1; mask < p3[n]; mask++) prv[mask] = -INF;
    for (int j = 0; j < m; j++) for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < p3[n]; mask++) {
            int bit = get(mask, i);
            if (!bit) {
                if (grid[i][j] == 'o') {
                    dp[i][j][mask] = -INF;
                    continue;
                }
                tie(dp[i][j][mask], backtrack[i][j][mask]) = max({
                        make_pair(prv[mask], mask),
                        make_pair(prv[mask + p3[i]], mask + p3[i]),
                        make_pair(prv[mask + 2 * p3[i]] + is(i, j, 'm'), mask + 2 * p3[i])
                    });
                if (i > 1 && is(i, j, 'm') && get(mask, i - 1) && get(mask, i - 2)) dp[i][j][mask]++;
            } else if (bit == 1) {
                if (!is(i, j, 'o') || (j && grid[i][j - 1] == 'o')) {
                    dp[i][j][mask] = -INF;
                    continue;
                }
                dp[i][j][mask] = prv[mask - p3[i]],
                backtrack[i][j][mask] = mask - p3[i];
                if (i > 1 && get(mask, i - 1) && !get(mask, i - 2)) dp[i][j][mask]++;
            } else {
                if (!is(i, j, 'o') || !j || !is(i, j - 1, 'o')) {
                    dp[i][j][mask] = -INF;
                    continue;
                }
                tie(dp[i][j][mask], backtrack[i][j][mask]) = max({
                        make_pair(prv[mask], mask),
                        make_pair(prv[mask - p3[i]] + (j > 1 && is(i, j - 2, 'm')), mask - p3[i])
                    });
                if (i > 1 && get(mask, i - 1) && !get(mask, i - 2) && is(i - 2, j, 'm')) dp[i][j][mask]++;
            }
        }
        for (int mask = 0; mask < p3[n]; mask++) prv[mask] = dp[i][j][mask];
    }

    int mask = max_element(prv, prv + p3[n]) - prv;
    cout << dp[n - 1][m - 1][mask] << '\n';
    for (int j = m - 1; ~j; j--) for (int i = n - 1; ~i; i--) {
        if (grid[i][j] == '?') grid[i][j] = (get(mask, i) ? 'o' : 'm');
        mask = backtrack[i][j][mask];
    }
    for (int i = 0; i < n; i++) cout << grid[i] << '\n';
    return 0;
}
