/*
APIO 2013 Robots
- end_pos[x][y][dir] = Position a robot ends up at if you push it in direction dir from square (x, y)
    - Do several DFS's to find this in like O(HW) or something
- dp[x][y][low][high] = Minimum number of pushes to get a low--high robot at square (x, y)
- For some (low, high),
    - First, dp[x][y][low][high] = min(dp[x][y][low][med] + dp[x][y][med + 1][high])
        - i.e. process merges
    - Then do a BFS to update the other dp[x'][y'] for (low, high)
        - dp[end_pos[x][y]][low][high] = min(dp[end_pos[x][y]][low][high], dp[x][y][low][high] + 1)
        - Notice how the maximum number of moves is around O(H^2), so we can BFS efficiently
          in O(HW + H^2)
- Complexity: O(N^2 * (HW + H^2))
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

const int INF = 250000;

int n, h, w;
char g[500][500];
pair<int, int> end_pos[500][500][4];
int dp[500][500][9][9];
vector<pair<int, int>> q[INF];

bool inside(int x, int y) {
    return (x >= 0 && y >= 0 && x < h && y < w && g[x][y] != 'x');
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> w >> h;
    memset(dp, 0x3f, sizeof(dp));

    FOR(i, 0, h) FOR(j, 0, w) {
        cin >> g[i][j];
        if (g[i][j] - '0' > 0 && g[i][j] - '0' < 10) {
            dp[i][j][g[i][j] - '1'][g[i][j] - '1'] = 0;
        }
    }

    // Determine final positions from each push
    FOR(i, 0, h) FOR(j, 0, w) if (g[i][j] != 'x') {
        FOR(k, 0, 4) {
            pair<int, int> pos = {i, j};
            int d = (k + (g[i][j] == 'A') * 3 + (g[i][j] == 'C')) % 4;  // NESW

            while (true) {
                if (d == 0) {
                    if (inside(pos.first - 1, pos.second)) pos.first--;
                    else break;
                } else if (d == 1) {
                    if (inside(pos.first, pos.second + 1)) pos.second++;
                    else break;
                } else if (d == 2) {
                    if (inside(pos.first + 1, pos.second)) pos.first++;
                    else break;
                } else {
                    if (inside(pos.first, pos.second - 1)) pos.second--;
                    else break;
                }

                if (g[pos.first][pos.second] == 'A') d = (d + 3) % 4;
                if (g[pos.first][pos.second] == 'C') d = (d + 1) % 4;
            }

            end_pos[i][j][k] = pos;
        }
    }

    // Find the minimum no. of pushes to get robot k-l to block (i, j)
    FOR(rng, 0, n) {
        FOR(k, 0, n - rng) {
            int l = k + rng;
            FOR(i, 0, h) FOR(j, 0, w) if (g[i][j] != 'x') {
                FOR(d, k, l) {
                    dp[i][j][k][l] =
                        min(dp[i][j][k][l],
                            dp[i][j][k][d] + dp[i][j][d + 1][l]);
                }
            }
        }

        FOR(k, 0, n - rng) {
            int l = k + rng;

            FOR(i, 0, h) FOR(j, 0, w) if (g[i][j] != 'x') {
                if (dp[i][j][k][l] <= INF) q[dp[i][j][k][l]].push_back({i, j});
            }
            
            FOR(i, 0, INF) {
                for (pair<int, int> pos : q[i]) {
                    int x, y;
                    tie(x, y) = pos;
                    if (dp[x][y][k][l] == i) {
                        FOR(d, 0, 4) {
                            int nx, ny;
                            tie(nx, ny) = end_pos[x][y][d];
                            if (dp[nx][ny][k][l] > dp[x][y][k][l] + 1) {
                                q[dp[nx][ny][k][l] = dp[x][y][k][l] + 1].push_back({nx, ny});
                            }
                        }
                    }
                }
                q[i].clear();
            }
        }
    }

    int ans = INT_MAX;
    FOR(i, 0, h) FOR(j, 0, w) ans = min(ans, dp[i][j][0][n - 1]);
    cout << (ans > INF ? -1 : ans);
    return 0;
}