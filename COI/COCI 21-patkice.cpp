#include <bits/stdc++.h>
using namespace std;

char grid[100][100];
int n, m, sx, sy, dx, dy;

int is_good(int x, int y) {
    int cnt = 0;
    while (1) {
        if (grid[x][y] == '.' || grid[x][y] == 'o') return INT_MAX;
        else if (grid[x][y] == 'x') return cnt;
        else if (grid[x][y] == '^') x--;
        else if (grid[x][y] == 'v') x++;
        else if (grid[x][y] == '<') y--;
        else if (grid[x][y] == '>') y++;
        cnt++;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
        if (grid[i][j] == 'o') sx = i, sy = j;
        if (grid[i][j] == 'x') dx = i, dy = j;
    }
    pair<int, string> ans = {INT_MAX - 1, ":(\n"};
    ans = min(ans, {is_good(sx + 1, sy), ":)\nS\n"});
    ans = min(ans, {is_good(sx - 1, sy), ":)\nN\n"});
    ans = min(ans, {is_good(sx, sy + 1), ":)\nE\n"});
    ans = min(ans, {is_good(sx, sy - 1), ":)\nW\n"});
    cout << ans.second;
    return 0;
}