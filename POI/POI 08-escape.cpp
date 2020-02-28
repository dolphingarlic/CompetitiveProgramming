/*
POI 2008 The Great Escape
- Firstly, notice that the path must form a spiral
- After each turn, there is some rectangle that Al Bytone can move in,
  which he enters into from some corner
    - For convenience, mirror the grid vertically so Al Bytone enters
      from the north and he only turns left
- dp[x][y][width][s_perim][dir] = Number of ways to get_dp to the hideout
                                    such that the north-west corner is
                                    (x, y), the width of the rectangle is
                                    width, the semiperimeter is s_perim,
                                    and Al Bytone enters from direction dir
                                    (0, 1, 2, 3 = N, W, S, E)
- For example, consider if Al Bytone enters from the north and the state
rectangle is ((x1, y1), (x2, y2), 0)
    - If he turns left at (x2, y1) then he enters the state ((x1, y1  + 1), (x2,
y2), 1)
        - To check if he can turn there, we can use prefix sums to check if a
path is clear
    - If he doesn't turn left there, we can effectively remove row x2 and thus
we add state ((x1, y1), (x2 - 1, y2), 0) to our answer
- Notice how each dp state only depends on the one with semiperimeter 1 less
than itself
    - This means we only need to store the previous states with semiperimeter 1
less than the current state
- Complexity: O(N^4)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

char grid[105];
int police[105][105], pref[105][105];
int dp[105][105][105][2][4];

int path(int x1, int y1, int x2, int y2) {
    return pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] +
           pref[x1 - 1][y1 - 1];
}

int get_dp(int x1, int y1, int x2, int y2, int s_perim, int dir) {
    if (x1 > x2 || y1 > y2) return 0;
    return dp[x1][y1][y2 - y1 + 1][1 - s_perim][dir];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k, tx, ty;
    cin >> n >> m >> k >> ty >> tx;
    tx = n - tx + 1;
    FOR(i, 0, n) {
        cin >> grid;
        FOR(j, 1, m + 1) police[n - i][j] = (grid[j - 1] == '*');
    }
    FOR(i, 1, n + 1) FOR(j, 1, m + 1)
        pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + police[i][j];

    FOR(i, 0, 4) dp[tx][ty][1][0][i] = 1;
    FOR(s_perim, 3, n + m + 1) {
        FOR(width, 0, s_perim + 1) {
            int height = s_perim - width;

            FOR(x1, 1, n - height + 2) FOR(y1, 1, m - width + 2) {
                int x2 = x1 + height - 1, y2 = y1 + width - 1;

                if (tx < x1 || x2 < tx || ty < y1 || y2 < ty) {
                    FOR(i, 0, 4) dp[x1][y1][width][s_perim & 1][i] = 0;
                } else {
                    dp[x1][y1][width][s_perim & 1][0] =
                        get_dp(x1, y1, x2 - 1, y2, s_perim & 1, 0);
                    dp[x1][y1][width][s_perim & 1][1] =
                        get_dp(x1, y1, x2, y2 - 1, s_perim & 1, 1);
                    dp[x1][y1][width][s_perim & 1][2] =
                        get_dp(x1 + 1, y1, x2, y2, s_perim & 1, 2);
                    dp[x1][y1][width][s_perim & 1][3] =
                        get_dp(x1, y1 + 1, x2, y2, s_perim & 1, 3);

                    if (y1 == ty && x1 <= tx && tx <= x2 && !path(x1, y1, x2, y1))
                        dp[x1][y1][width][s_perim & 1][0] = 1;
                    if (x2 == tx && y1 <= ty && ty <= y2 && !path(x2, y1, x2, y2))
                        dp[x1][y1][width][s_perim & 1][1] = 1;
                    if (y2 == ty && x1 <= tx && tx <= x2 && !path(x1, y2, x2, y2))
                        dp[x1][y1][width][s_perim & 1][2] = 1;
                    if (x1 == tx && y1 <= ty && ty <= y2 && !path(x1, y1, x1, y2))
                        dp[x1][y1][width][s_perim & 1][3] = 1;

                    if (!path(x1, y1, x2, y1))
                        dp[x1][y1][width][s_perim & 1][0] += get_dp(x1, y1 + 1, x2, y2, s_perim & 1, 1);
                    if (!path(x2, y1, x2, y2))
                        dp[x1][y1][width][s_perim & 1][1] += get_dp(x1, y1, x2 - 1, y2, s_perim & 1, 2);
                    if (!path(x1, y2, x2, y2))
                        dp[x1][y1][width][s_perim & 1][2] += get_dp(x1, y1, x2, y2 - 1, s_perim & 1, 3);
                    if (!path(x1, y1, x1, y2))
                        dp[x1][y1][width][s_perim & 1][3] += get_dp(x1 + 1, y1, x2, y2, s_perim & 1, 0);

                    for (int dr = 0; dr < 4; dr++)
                        if (dp[x1][y1][width][s_perim & 1][dr] >= k) dp[x1][y1][width][s_perim & 1][dr] -= k;
                }
            }
        }
    }
    cout << dp[1][1][m][(n + m) & 1][0];
    return 0;
}