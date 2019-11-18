#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll h[2020][2020], ans[2020][2020];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n + 1) {
        vector<pair<int, int>> v = {{0, 0}};
        FOR(j, 1, m + 1) {
            h[i][j] = h[i - 1][j] + 1;
            char c;
            cin >> c;
            if (c == '#') h[i][j] = 0;

            while (v.size() && v.back().second >= h[i][j]) v.pop_back();
            v.push_back({j, h[i][j]});

            for (int k = v.size() - 1; k; k--) {
                ans[v[k].second][j - v[k - 1].first]++;
                ans[v[k - 1].second][j - v[k - 1].first]--;
            }
        }
    }

    for (int i = n; i; i--) for (int j = m; j; j--) {
        ans[i][j] += ans[i + 1][j] + ans[i][j + 1] - ans[i + 1][j + 1];
    }

    ll tot = 0;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) tot += i * j * ans[i][j];
    cout << tot;
    return 0;
}