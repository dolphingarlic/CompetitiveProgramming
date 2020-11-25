#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;
 
int n, m;
char orientation[2]{'\\', '/'};
bool correct[501][501];
int visited[501][501], dx[4]{-1, -1, 1, 1}, dy[4]{-1, 1, -1, 1};
pair<int, int> dz[4]{{-1, -1}, {-1, 0}, {0, -1}, {0, 0}};
 
bool inside(int x, int y) {
    return (~x && x <= n && ~y && y <= m);
}
 
int main() {
    cin >> n >> m;
 
    FOR(i, 0, n) FOR(j, 0, m) {
        char c;
        cin >> c;
        if (c == orientation[(i + j) & 1]) correct[i][j] = true;
        else correct[i][j] = false;
    }
 
    deque<pair<int, pair<int, int>>> dq;
    dq.push_back({1, {0, 0}});
    while (dq.size()) {
        int x, y, z;
        tie(x, y) = dq.front().second;
        z = dq.front().first;
        dq.pop_front();
        if (visited[x][y]) continue;
        visited[x][y] = z;
 
        FOR(i, 0, 4) {
            int nx = x + dx[i], ny = y + dy[i];
            if (inside(nx, ny) && !visited[nx][ny]) {
                if (correct[x + dz[i].first][y + dz[i].second]) {
                    dq.push_front({z, {nx, ny}});
                } else {
                    dq.push_back({z + 1, {nx, ny}});
                }
            }
        }
    }
 
    if (visited[n][m]) cout << visited[n][m] - 1;
    else cout << "NO SOLUTION";
    return 0;
}
