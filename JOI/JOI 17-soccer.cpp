/*
JOI 2017 Soccer
- First, find the minimum distance to any player for each coordinate
- Notice how the game will look like
    - Run a few steps
    - Kick the ball
    - Another player goes to the ball
    - Repeat
- Then we just do Dijkstra
- Complexity: O(H^3)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Ball {
    int x, y, d;
    ll f;
};

bool operator<(Ball A, Ball B) { return A.f > B.f; }

int h, w;
ll vert[501][501], to_p[501][501], dp[501][501][6];
bool visited[501][501][6];
int dx[6]{0, 0, 0, 0, 1, -1}, dy[6]{0, 0, 1, -1, 0, 0};

bool inside(int x, int y) { return (~x && ~y && x <= h && y <= w); }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll a, b, c;
    Ball dest;
    priority_queue<Ball> pq;
    cin >> h >> w >> a >> b >> c >> n;

    memset(vert, 0x3f, sizeof(vert));
    memset(to_p, 0x3f, sizeof(to_p));
    memset(dp, 0x3f, sizeof(dp));
    FOR(i, 0, n) {
        int x, y;
        cin >> x >> y;
        vert[x][y] = 0;
        if (!i) pq.push({x, y, 1, 0}), dp[x][y][1] = 0;
        if (i == n - 1) dest = {x, y, 0, 0};
    }

    FOR(i, 1, h + 1) FOR(j, 0, w + 1) {
        vert[i][j] = min(vert[i][j], vert[i - 1][j] + 1);
        vert[h - i][j] = min(vert[h - i][j], vert[h - i + 1][j] + 1);
    }
    FOR(i, 0, h + 1) FOR(j, 0, w + 1) FOR(k, 0, w + 1) {
        to_p[i][j] = min(to_p[i][j], vert[i][k] + abs(j - k));
    }

    while (pq.size()) {
        Ball curr = pq.top();
        pq.pop();

        if (!visited[curr.x][curr.y][curr.d]) {
            visited[curr.x][curr.y][curr.d] = true;

            // Ball is at (x, y)
            if (!curr.d) {  // Nearest player runs to ball
                if (curr.f + to_p[curr.x][curr.y] * c < dp[curr.x][curr.y][1]) {
                    dp[curr.x][curr.y][1] = curr.f + to_p[curr.x][curr.y] * c;
                    pq.push({curr.x, curr.y, 1, curr.f + to_p[curr.x][curr.y] * c});
                }
            } else if (curr.d == 1) {  // Player has ball
                FOR(i, 2, 6) {
                    // Player runs in direction i with the ball
                    int nx = curr.x + dx[i], ny = curr.y + dy[i];
                    if (inside(nx, ny) && curr.f + c < dp[nx][ny][1]) {
                        dp[nx][ny][1] = curr.f + c;
                        pq.push({nx, ny, 1, curr.f + c});
                    }
                    // Player kicks the ball in direction i
                    if (curr.f + b < dp[curr.x][curr.y][i]) {
                        dp[curr.x][curr.y][i] = curr.f + b;
                        pq.push({curr.x, curr.y, i, curr.f + b});
                    }
                }
            } else {  // Ball is/was moving in direction d
                // Ball continues in the direction
                int nx = curr.x + dx[curr.d], ny = curr.y + dy[curr.d];
                if (inside(nx, ny) && curr.f + a < dp[nx][ny][curr.d]) {
                    dp[nx][ny][curr.d] = curr.f + a;
                    pq.push({nx, ny, curr.d, curr.f + a});
                }
                // Ball stops
                if (curr.f < dp[curr.x][curr.y][0]) {
                    dp[curr.x][curr.y][0] = curr.f;
                    pq.push({curr.x, curr.y, 0, curr.f});
                }
            }
        }
    }

    ll ans = LLONG_MAX;
    FOR(i, 0, 6) ans = min(ans, dp[dest.x][dest.y][i]);
    cout << ans;
    return 0;
}