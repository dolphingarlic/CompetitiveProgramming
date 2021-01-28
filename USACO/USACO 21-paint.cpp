/*
USACO 2021 Paint by Letters
- http://usaco.org/current/data/sol_prob3_platinum_jan21.html
- Very cool problem; whoever made it deserves a medal ;)
- Complexity: O(NM + Q(N + M))
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, q;
char grid[2001][2001];
pair<int, int> cmp[2002][2002], d[4]{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int s_pref[2002][2002], v_pref[2002][2002], h_pref[2002][2002];
bool deleted[2002][2002];

bool inside(int x, int y, int nx, int ny) {
    if (!(~nx && ~ny && nx <= n + 1 && ny <= m + 1)) return false;
    if (nx == x + 1) return grid[x][y] != grid[x][y - 1];
    if (nx == x - 1) return grid[nx][y] != grid[nx][y - 1];
    if (ny == y + 1) return grid[x][y] != grid[x - 1][y];
    return grid[x][ny] != grid[x - 1][ny];
}

void dfs(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int nx = x + d[i].first, ny = y + d[i].second;
        if (inside(x, y, nx, ny)) {
            if (nx == x + 1) v_pref[x][y] = 1;
            else if (nx == x - 1) v_pref[nx][y] = 1;
            else if (ny == y + 1) h_pref[x][y] = 1;
            else h_pref[x][ny] = 1;

            if (!cmp[nx][ny].first) {
                cmp[nx][ny] = cmp[x][y];
                dfs(nx, ny);
            }
        }
    }
}

bool bad(int x, int y, int x1, int y1, int x2, int y2) {
    int a = cmp[x][y].first, b = cmp[x][y].second;
    if (a > x1 && a <= x2 && b > y1 && b <= y2 && !deleted[a][b]) {
        deleted[a][b] = true;
        return true;
    }
    return false;
}

void reset(int x, int y) {
    int a = cmp[x][y].first, b = cmp[x][y].second;
    deleted[a][b] = false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> grid[i][j];
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= m + 1; j++)
            if (!cmp[i][j].first) {
                s_pref[i][j] = 1;
                cmp[i][j] = {i, j};
                dfs(i, j);
            }
    for (int i = 1; i <= n + 1; i++)
        for (int j = 1; j <= m + 1; j++) {
            s_pref[i][j] += s_pref[i - 1][j] + s_pref[i][j - 1] - s_pref[i - 1][j - 1];
            v_pref[i][j] += v_pref[i - 1][j] + v_pref[i][j - 1] - v_pref[i - 1][j - 1];
            h_pref[i][j] += h_pref[i - 1][j] + h_pref[i][j - 1] - h_pref[i - 1][j - 1];
        }
    while (q--) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int E = v_pref[x2][y2] - v_pref[x2][y1] - v_pref[x1 - 1][y2] + v_pref[x1 - 1][y1] +
                h_pref[x2][y2] - h_pref[x2][y1 - 1] - h_pref[x1][y2] + h_pref[x1][y1 - 1];
        int V = (x2 - x1) * (y2 - y1);
        int C = s_pref[x2][y2] - s_pref[x2][y1] - s_pref[x1][y2] + s_pref[x1][y1];
        for (int i = x1; i <= x2 + 1; i++) {
            if (bad(i, y2 + 1, x1, y1, x2, y2)) C--;
            if (bad(i, y1, x1, y1, x2, y2)) C--;
        }
        for (int i = y1; i <= y2 + 1; i++) {
            if (bad(x2 + 1, i, x1, y1, x2, y2)) C--;
            if (bad(x1, i, x1, y1, x2, y2)) C--;
        }
        for (int i = x1; i <= x2 + 1; i++) {
            reset(i, y2 + 1);
            reset(i, y1);
        }
        for (int i = y1; i <= y2 + 1; i++) {
            reset(x2 + 1, i);
            reset(x1, i);
        }
        cout << E - V + C + 1 << '\n';
    }
    return 0;
}
