#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int h[1001][1001], pref[1001][1001];
pair<int, int> dp1[1001][1001];
pair<int, pair<int, int>> dp2[1001][1001];

int rect(int x1, int y1, int x2, int y2) {
    return pref[x2][y2] - pref[x2][y1 - 1] - pref[x1 - 1][y2] +
           pref[x1 - 1][y1 - 1];
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int m, n, a, b, c, d;
    cin >> m >> n >> a >> b >> c >> d;

    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        cin >> h[i][j];
        pref[i][j] =
            pref[i - 1][j] + pref[i][j - 1] + h[i][j] - pref[i - 1][j - 1];
    }

    FOR(i, 2, n) {
        set<pair<int, int>> s;
        FOR(j, 2, a - c) s.insert({rect(i, j, i + d - 1, j + c - 1), j});

        FOR(j, a - c, m - c + 1) {
            s.insert({rect(i, j, i + d - 1, j + c - 1), j});
            dp1[i][j - (a - c - 2)] = *s.begin();
            s.erase(
                {rect(i, j - (a - c - 2), i + d - 1, j - (a - c - 2) + c - 1),
                 j - (a - c - 2)});
        }
    }

    FOR(i, 2, m) {
        set<pair<int, pair<int, int>>> s;
        FOR(j, 2, b - d) s.insert({dp1[j][i].first, {dp1[j][i].second, j}});

        FOR(j, b - d, n - d + 1) {
            s.insert({dp1[j][i].first, {dp1[j][i].second, j}});
            dp2[j - (b - d - 2)][i] = *s.begin();
            s.erase({dp1[j - (b - d - 2)][i].first,
                     {dp1[j - (b - d - 2)][i].second, j - (b - d - 2)}});
        }
    }

    int mx = 0;
    pair<int, int> ext_coords, int_coords;
    FOR(i, 1, n - b + 2) FOR(j, 1, m - a + 2) {
        if (rect(i, j, i + b - 1, j + a - 1) - dp2[i + 1][j + 1].first > mx) {
            mx = rect(i, j, i + b - 1, j + a - 1) - dp2[i + 1][j + 1].first;
            ext_coords = {j, i};
            int_coords = dp2[i + 1][j + 1].second;
        }
    }

    cout << ext_coords.first << ' ' << ext_coords.second << '\n';
    cout << int_coords.first << ' ' << int_coords.second;
    return 0;
}
