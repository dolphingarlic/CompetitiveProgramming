#include <iostream>
#include <string>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

int n, m, visited[1000][1000], dir[1000][1000];
int dx[4]{0, 0, 1, -1}, dy[4]{1, -1, 0, 0};
string s[1000];

bool good(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m && s[x][y] != '#';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    pair<int, int> src, dest;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'A') src = {i, j};
            else if (s[i][j] == 'B') dest = {i, j};
        }
    }
    queue<pair<int, int>> q;
    q.push(src);
    visited[src.first][src.second] = 1;
    while (q.size()) {
        int x, y;
        tie(x, y) = q.front();
        q.pop();

        if (make_pair(x, y) == dest) {
            cout << "YES\n" << visited[x][y] - 1 << '\n';
            string backtrack = "";
            for (int i = visited[x][y] - 1; i; i--) {
                int idx = dir[x][y];
                backtrack += "RLDU"[idx];
                x -= dx[idx], y -= dy[idx];
            }
            reverse(backtrack.begin(), backtrack.end());
            cout << backtrack;
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            if (good(x + dx[i], y + dy[i]) && !visited[x + dx[i]][y + dy[i]]) {
                visited[x + dx[i]][y + dy[i]] = visited[x][y] + 1;
                dir[x + dx[i]][y + dy[i]] = i;
                q.push({x + dx[i], y + dy[i]});
            }
        }
    }
    cout << "NO";
    return 0;
}
