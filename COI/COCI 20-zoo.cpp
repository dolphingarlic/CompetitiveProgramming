#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};

int n, m, depth[1000][1000], ans = 1;
string snow[1000];

bool inside(int x, int y) {
    return (x > -1 && x < n && y > -1 && y < m && snow[x][y] != '*');
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    FOR(i, 0, n) cin >> snow[i];

    deque<pair<int, int>> q;
    q.push_back({0, 0});
    depth[0][0] = 1;

    while (q.size()) {
        pair<int, int> c = q.front();
        q.pop_front();
        ans = max(ans, depth[c.first][c.second]);

        FOR(i, 0, 4) {
            int x = c.first + dx[i], y = c.second + dy[i];
            if (inside(x, y) && depth[x][y] == 0) {
                if (snow[x][y] == snow[c.first][c.second]) {
                    depth[x][y] = depth[c.first][c.second];
                    q.push_front({x, y});
                } else {
                    depth[x][y] = depth[c.first][c.second] + 1;
                    q.push_back({x, y});
                }
            }
        }
    }

    cout << ans;
    return 0;
}