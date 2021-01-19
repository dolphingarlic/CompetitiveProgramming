/*
COCI 2021 Patkice 2
- Do a 0/1 BFS where the cost is 0 if you don't change the current character and the cost is 1 otherwise
- Complexity: O(NM)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int dx[4]{1, 0, 0, -1}, dy[4]{0, 1, -1, 0};
const string cd = "v><^";

int n, m, sx, sy, tx, ty, visited[2000][2000];
char grid[2000][2000], prv_c[2000][2000];
pair<int, int> prv_p[2000][2000];

bool inside(int x, int y) { return (x >= 0 && y >= 0 && x < n && y < m); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
        if (grid[i][j] == 'o') sx = i, sy = j;
        if (grid[i][j] == 'x') tx = i, ty = j;
    }

    deque<tuple<int, int, int, int, int, char>> dq;
    dq.push_back({sx, sy, sx, sx, 1, 'o'});
    visited[sx][sy] = 0;
    while (dq.size()) {
        int x, y, px, py, d;
        char c;
        tie(x, y, px, py, d, c) = dq.front();
        dq.pop_front();
        if (visited[x][y]) continue;
        visited[x][y] = visited[px][py] + d;
        prv_c[x][y] = c;
        prv_p[x][y] = {px, py};

        for (int i = 0; i < 4; i++) if (inside(x + dx[i], y + dy[i]) && !visited[x + dx[i]][y + dy[i]]) {
            if (grid[x][y] == cd[i]) {
                dq.push_front({x + dx[i], y + dy[i], x, y, 0, cd[i]});
            } else {
                dq.push_back({x + dx[i], y + dy[i], x, y, 1, cd[i]});
            }
        }
    }

    cout << visited[tx][ty] - 2 << '\n';
    while (prv_p[tx][ty] != make_pair(sx, sy)) {
        int nx, ny;
        tie(nx, ny) = prv_p[tx][ty];
        grid[nx][ny] = prv_c[tx][ty];
        tx = nx, ty = ny;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << grid[i][j];
        cout << '\n';
    }
    return 0;
}
