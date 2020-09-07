/*
IOI 2003 Amazing Robots
- Cancer + BFS (just... do it)
- No wonder so few IOI 2003 contestants solved this problem...
- Complexity: O(R1 * C1 * R2 * C2 * (G1 + G2) * 12)
*/

#include <bits/stdc++.h>
#define State tuple<int, int, int, int, int>
typedef long long ll;
using namespace std;

struct Guard {
    int x, y, p, dx, dy;
    char d;

    pair<int, int> loc(int t) {
        t %= 2 * (p - 1);
        if (t > p - 1) {
            return {x + dx * (2 * (p - 1) - t), y + dy * (2 * (p - 1) - t)};
        } else {
            return {x + dx * t, y + dy * t};
        }
    }
} guards1[11], guards2[11];

int r1, c1, ix1, iy1, g1, r2, c2, ix2, iy2, g2;
int visited[22][22][22][22][12], dx[4] = {-1, 0, 0, 1}, dy[4] = {0, 1, -1, 0};
char m1[22][22], m2[22][22], backtrack[22][22][22][22][12];
string dir = "NEWS";
State prv[22][22][22][22][12];

State moveto(int x1, int y1, int x2, int y2, int t, int dx, int dy) {
    if (x1 && y1 && x1 <= r1 && y1 <= c1 && m1[x1 + dx][y1 + dy] != '#') x1 += dx, y1 += dy;
    if (x2 && y2 && x2 <= r2 && y2 <= c2 && m2[x2 + dx][y2 + dy] != '#') x2 += dx, y2 += dy;
    t++;
    if (t == 12) t -= 12;
    return State(x1, y1, x2, y2, t);
}

bool canmove(int x1, int y1, int x2, int y2, int t, int dx, int dy) {
    int nx1, ny1, nx2, ny2, nt;
    tie(nx1, ny1, nx2, ny2, nt) = moveto(x1, y1, x2, y2, t, dx, dy);
    if (visited[nx1][ny1][nx2][ny2][nt]) return false;
    for (int i = 1; i <= g1; i++) {
        int gx, gy, ngx, ngy;
        tie(gx, gy) = guards1[i].loc(t);
        tie(ngx, ngy) = guards1[i].loc(nt);
        if ((ngx == nx1 && ngy == ny1) || (gx == nx1 && gy == ny1 && ngx == x1 && ngy == y1)) return false;
    }
    for (int i = 1; i <= g2; i++) {
        int gx, gy, ngx, ngy;
        tie(gx, gy) = guards2[i].loc(t);
        tie(ngx, ngy) = guards2[i].loc(nt);
        if ((ngx == nx2 && ngy == ny2) || (gx == nx2 && gy == ny2 && ngx == x2 && ngy == y2)) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> r1 >> c1;
    for (int i = 1; i <= r1; i++) for (int j = 1; j <= c1; j++) {
        cin >> m1[i][j];
        if (m1[i][j] == 'X') ix1 = i, iy1 = j;
    }
    cin >> g1;
    for (int i = 1; i <= g1; i++) {
        cin >> guards1[i].x >> guards1[i].y >> guards1[i].p >> guards1[i].d;
        guards1[i].dx = dx[find(dir.begin(), dir.end(), guards1[i].d) - dir.begin()];
        guards1[i].dy = dy[find(dir.begin(), dir.end(), guards1[i].d) - dir.begin()];
    }

    cin >> r2 >> c2;
    for (int i = 1; i <= r2; i++) for (int j = 1; j <= c2; j++) {
        cin >> m2[i][j];
        if (m2[i][j] == 'X') ix2 = i, iy2 = j;
    }
    cin >> g2;
    for (int i = 1; i <= g2; i++) {
        cin >> guards2[i].x >> guards2[i].y >> guards2[i].p >> guards2[i].d;
        guards2[i].dx = dx[find(dir.begin(), dir.end(), guards2[i].d) - dir.begin()];
        guards2[i].dy = dy[find(dir.begin(), dir.end(), guards2[i].d) - dir.begin()];
    }

    queue<State> q;
    q.push(State(ix1, iy1, ix2, iy2, 0));
    visited[ix1][iy1][ix2][iy2][0] = 1;
    while (q.size()) {
        int x1, y1, x2, y2, t;
        tie(x1, y1, x2, y2, t) = q.front();
        q.pop();

        // Escaped
        if ((!x1 || !y1 || x1 > r1 || y1 > c1) && (!x2 || !y2 || x2 > r2 || y2 > c2)) {
            int moves = visited[x1][y1][x2][y2][t] - 1;
            cout << moves << '\n';
            vector<char> seq;
            for (int i = 0; i < moves; i++) {
                seq.push_back(backtrack[x1][y1][x2][y2][t]);
                tie(x1, y1, x2, y2, t) = prv[x1][y1][x2][y2][t];
            }
            reverse(seq.begin(), seq.end());
            for (char i : seq) cout << i << '\n';
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            if (canmove(x1, y1, x2, y2, t, dx[i], dy[i])) {
                int nx1, ny1, nx2, ny2, nt;
                tie(nx1, ny1, nx2, ny2, nt) = moveto(x1, y1, x2, y2, t, dx[i], dy[i]);
                visited[nx1][ny1][nx2][ny2][nt] = visited[x1][y1][x2][y2][t] + 1;
                backtrack[nx1][ny1][nx2][ny2][nt] = dir[i];
                prv[nx1][ny1][nx2][ny2][nt] = State(x1, y1, x2, y2, t);
                q.push(State(nx1, ny1, nx2, ny2, nt));
            }
        }
    }
    cout << "-1\n";
    return 0;
}