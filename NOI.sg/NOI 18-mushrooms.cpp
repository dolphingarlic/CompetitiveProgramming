#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int r, c;
vector<vector<int>> bit, pref;
vector<pair<int, int>> shrooms;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int d, k;
    cin >> r >> c >> d >> k;
    bit.resize(r + 1), pref.resize(r + 1);
    FOR(i, 0, r + 1) bit[i].resize(c + 1), pref[i].resize(c + 1);

    FOR(i, 1, r + 1) {
        FOR(j, 1, c + 1) {
            char c;
            cin >> c;
            if (c == 'S') bit[i][j] = 1;
            else if (c == 'M') shrooms.push_back({i, j});
            pref[i][j] = bit[i][j] + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }

    int ans = 0;
    for (pair<int, int> i : shrooms) {
        int x1 = min(r, i.first + d), x2 = max(0, i.first - d - 1), y1 = min(c, i.second + d), y2 = max(0, i.second - d - 1);
        int cnt = pref[x1][y1] - pref[x1][y2] - pref[x2][y1] + pref[x2][y2];
        if (cnt >= k) ans++;
    }
    cout << ans;
    return 0;
}