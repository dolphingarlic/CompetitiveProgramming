#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct State {
    int x, y, used;
};

char cave[500][500];
int visited[500][500][51], dx[4]{-1, 1, 0, 0}, dy[4]{0, 0, -1, 1};
pair<int, int> start, dest;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    FOR(i, 0, n) FOR(j, 0, m) {
        cin >> cave[i][j];
        if (cave[i][j] == 'S') start = {i, j};
        if (cave[i][j] == 'E') dest = {i, j};
    }

    queue<State> q;
    q.push({start.first, start.second, 0});
    visited[start.first][start.second][0] = 1;
    while (q.size()) {
        State curr = q.front();
        q.pop();
        FOR(i, 0, 4) {
            int nx = curr.x + dx[i], ny = curr.y + dy[i];
            if (nx > -1 && nx < n && ny > -1 && ny < m) {
                if (cave[curr.x + dx[i]][curr.y + dy[i]] == '#') {
                    if (curr.used < k && !visited[nx][ny][curr.used + 1]) {
                        visited[nx][ny][curr.used + 1] = visited[curr.x][curr.y][curr.used] + 1;
                        q.push({nx, ny, curr.used + 1});
                    }
                } else {
                    if (!visited[nx][ny][curr.used]) {
                        visited[nx][ny][curr.used] = visited[curr.x][curr.y][curr.used] + 1;
                        q.push({nx, ny, curr.used});
                    }
                }
            }
        }
    }

    int ans = INT_MAX;
    FOR(i, 0, k + 1) {
        if (visited[dest.first][dest.second][i])
            ans = min(ans, visited[dest.first][dest.second][i] - 1);
    }

    if (ans == INT_MAX) cout << -1;
    else cout << ans;
    return 0;
}