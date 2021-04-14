#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m;
string grid[500];
bool red[500][500], blue[500][500], needs[500], has[500];
int dx[4]{0, 0, 1, -1}, dy[4]{1, -1, 0, 0};

bool inside(int x, int y) {
    return (x > -1 && y > -1 && x < n && y < m && !blue[x][y] && (!red[x][y] || grid[x][y] == '#'));
}

void dfs(int x, int y) {
    blue[x][y] = true;
    for (int i = 0; i < 4; i++) if (inside(x + dx[i], y + dy[i]))
        dfs(x + dx[i], y + dy[i]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++)
            if (grid[i][j] == '#') red[i][j] = needs[i] = true;
    }
    for (int i = 1; i < n - 1; i++) {
        red[i][0] = true;
        if (needs[i] && !has[i - 1]) {
            for (int j = 1; j < m - 1; j++) red[i][j] = true;
            has[i] = true;
        }
    }
    dfs(0, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << (red[i][j] ? '#' : '.');
        cout << '\n';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << (blue[i][j] ? '#' : '.');
        cout << '\n';
    }
    return 0;
}
