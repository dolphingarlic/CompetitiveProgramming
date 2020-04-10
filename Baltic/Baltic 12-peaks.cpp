/*
Baltic 2012 Peaks
- http://www.boi2012.lv/data/day1/spoilers/peaks.pdf
- Complexity: O(NM log NM)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int h[2002][2002];
bool pl(pair<int, int> A, pair<int, int> B) {
    if (h[A.first][A.second] == h[B.first][B.second]) {
        if (A.first == B.first) return A.second < B.second;
        return A.first < B.first;
    }
    return h[A.first][A.second] > h[B.first][B.second];
}

bool is_peak[2002][2002];
pair<int, int> points[100000], cmp[2002][2002], peaks[2002][2002];
vector<pair<int, int>> ans, delta = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

pair<int, int> find(int x, int y) {
    while (x != cmp[x][y].first || y != cmp[x][y].second) {
        cmp[x][y] = cmp[cmp[x][y].first][cmp[x][y].second], tie(x, y) = cmp[x][y];
    }
    return {x, y};
}

void onion(int x1, int y1, int x2, int y2) {
    tie(x1, y1) = find(x1, y1);
    tie(x2, y2) = find(x2, y2);
    if (x1 == x2 && y1 == y2) return;

    cmp[x2][y2] = cmp[x1][y1];
    is_peak[x1][y1] &= is_peak[x2][y2];

    if (peaks[x1][y1].second) {
        if (peaks[x1][y1].first > peaks[x2][y2].first) {
            FOR(i, 0, peaks[x2][y2].second)
                ans.push_back({peaks[x2][y2].first, h[x1][y1]});
        } else if (peaks[x2][y2].first > peaks[x1][y1].first) {
            FOR(i, 0, peaks[x1][y1].second)
                ans.push_back({peaks[x1][y1].first, h[x1][y1]});
            peaks[x1][y1] = peaks[x2][y2];
        } else peaks[x1][y1].second += peaks[x2][y2].second;
    } else peaks[x1][y1] = peaks[x2][y2];
    peaks[x2][y2] = {0, 0};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, cnt = 0;
    cin >> n >> m;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        cin >> h[i][j];
        cmp[i][j] = {i, j};
        points[cnt++] = {i, j};
    }
    sort(points, points + cnt, pl);

    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        is_peak[i][j] = true;
        for (pair<int, int> d : delta)
            is_peak[i][j] &= (h[i][j] >= h[i + d.first][j + d.second]);
    }
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        for (pair<int, int> d : delta) {
            if (h[i][j] == h[i + d.first][j + d.second])
                onion(i, j, i + d.first, j + d.second);
        }
    }

    FOR(i, 0, cnt) {
        int x = points[i].first, y = points[i].second;
        if (is_peak[x][y] && find(x, y).first == x && find(x, y).second == y) peaks[x][y] = {h[x][y], 1};
        else {
            for (pair<int, int> d : delta) {
                int dx, dy;
                tie(dx, dy) = find(x + d.first, y + d.second);
                if (h[dx][dy] >= h[x][y]) onion(x, y, dx, dy);
            }
        }
    }

    FOR(i, 1, n + 1) FOR(j, 1, m + 1) FOR(k, 0, peaks[i][j].second) ans.push_back({peaks[i][j].first, 0});
    sort(ans.begin(), ans.end(), greater<pair<int, int>>());
    cout << ans.size() << '\n';
    for (pair<int, int> i : ans) cout << i.first << ' ' << i.second << '\n';
    return 0;
}