#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int l, w, k;
char grid[1026][1026];
int cmp = 1, v[1026][1026];
vector<pair<int, int>> d = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool available(int x, int y) {
    return x && y && x <= l && y <= w && grid[x][y] != '#' && !v[x][y] &&
           v[x + 1][y] + v[x - 1][y] + v[x][y + 1] + v[x][y - 1] ==
               max({v[x + 1][y], v[x - 1][y], v[x][y + 1], v[x][y - 1]});
}

int bfs(int x, int y) {
    queue<pair<int, int>> q;
    v[x][y] = cmp;
    q.push({x, y});
    int ret = 0;
    while (q.size()) {
        tie(x, y) = q.front();
        q.pop();

        int cnt = 0;
        random_shuffle(d.begin(), d.end());
        for (pair<int, int> i : d) {
            if (available(x + i.first, y + i.second)) {
                v[x + i.first][y + i.second] = cmp;
                q.push({x + i.first, y + i.second});
                cnt++;
            }
        }
        if (!cnt) ret++;
    }
    return ret;
}

int main() {
    srand(69420);
    cin >> l >> w >> k;
    FOR(i, 1, l + 1) FOR(j, 1, w + 1) cin >> grid[i][j];

    vector<pair<int, int>> to_process;
    FOR(i, 1, l + 1) FOR(j, 1, w + 1) to_process.push_back({i, j});
    random_shuffle(to_process.begin(), to_process.end());

    pair<int, pair<int, int>> opt = {0, {1, 1}};
    for (pair<int, int> i : to_process) if (available(i.first, i.second)) {
        opt = max(opt, {bfs(i.first, i.second), {i.first, i.second}});
        cmp++;
    }
    cerr << min(10.0, 10.0 * opt.first / k) << '\n';

    FOR(i, 1, l + 1) {
        FOR(j, 1, w + 1) {
            if (grid[i][j] == '.' &&
                v[i][j] != v[opt.second.first][opt.second.second])
                cout << 'X';
            else
                cout << grid[i][j];
        }
        cout << '\n';
    }
    return 0;
}