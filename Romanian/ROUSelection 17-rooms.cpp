/*
Romanian IOI Selection 2017 Rooms
- For each room, let the topmost cell be the "special" cell
    - If the special cell is in the query rectangle, so is the room
    - We can find the number of special cells in a rectangle easily with
      prefix sums
- If the special cell is not in the rectangle but the room is, then the room
  must have at least 1 cell on the border of the rectangle
    - So we can just traverse the border of the rectangle and look for stray rooms
- Complexity: O(Q(M + N))
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m, has_room[2001][2001], pref[2001][2001];
char grid[2001][2001];
pair<int, int> special[2001][2001], d[4]{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool included[2001][2001];

bool inside(int x, int y, char c) { return (x && y && x <= n && y <= m && grid[x][y] == c); }

bool outside(int x, int y, int x1, int y1, int x2, int y2) {
    int a = special[x][y].first, b = special[x][y].second;
    if ((a < x1 || a > x2 || b < y1 || b > y2) && !included[a][b]) {
        included[a][b] = true;
        return true;
    }
    return false;
}

void deactivate(int x, int y) {
    int a = special[x][y].first, b = special[x][y].second;
    included[a][b] = false;
}

void dfs(int x, int y) {
    FOR(i, 0, 4) {
        int nx = x + d[i].first, ny = y + d[i].second;
        if (inside(nx, ny, grid[x][y]) && !special[nx][ny].first) {
            special[nx][ny] = special[x][y];
            dfs(nx, ny);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) cin >> grid[i][j];
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) if (!special[i][j].first) {
        has_room[i][j]++;
        special[i][j] = {i, j};
        dfs(i, j);
    }
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        pref[i][j] = has_room[i][j] + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }

    int q;
    cin >> q;
    while (q--) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        int ans = pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1];
        FOR(i, x1, x2 + 1) {
            if (outside(i, y1, x1, y1, x2, y2)) ans++;
            if (outside(i, y2, x1, y1, x2, y2)) ans++;
        }
        FOR(i, y1, y2 + 1) {
            if (outside(x1, i, x1, y1, x2, y2)) ans++;
            if (outside(x2, i, x1, y1, x2, y2)) ans++;
        }
        cout << ans << '\n';

        FOR(i, x1, x2 + 1) {
            deactivate(i, y1);
            deactivate(i, y2);
        }
        FOR(i, y1, y2 + 1) {
            deactivate(x1, i);
            deactivate(x2, i);
        }
    }
    return 0;
}