/*
USACO 2019 Mowing
- dp[lis][i] = min(dp[lis - 1][j] + (x[i] - x[j]) * (y[i] - y[j]))
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
typedef long long ll;
using namespace std;

pair<int, int> f[200002];
vector<int> lis;
vector<vector<pair<int, pair<int, int>>>> has_lis;
ll dp[200002];

ll eval(int idx, pair<int, int> a, pair<int, int> b) {
    return dp[idx] + ll(a.x - b.x) * ll(a.y - b.y);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("mowing.in");
    ofstream cout("mowing.out");

    int n, t;
    cin >> n >> t;
    FOR(i, 0, n) cin >> f[i].x >> f[i].y;
    f[n++] = {0, 0};
    f[n++] = {t, t};
    sort(f, f + n);

    FOR(i, 0, n) {
        int pos = lower_bound(lis.begin(), lis.end(), f[i].y) - lis.begin();
        if (pos == lis.size()) {
            lis.push_back(f[i].y);
            has_lis.push_back({{i, f[i]}});
        } else {
            lis[pos] = f[i].y;
            has_lis[pos].push_back({i, f[i]});
        }
    }

    FOR(i, 1, has_lis.size()) {
        for (auto j : has_lis[i]) {
            dp[j.x] = LLONG_MAX;
            for (auto k : has_lis[i - 1]) {
                if (k.y.x < j.y.x) {
                    if (k.y.y < j.y.y) {
                        dp[j.x] = min(dp[j.x], eval(k.x, k.y, j.y));
                    }
                } else break;
            }
        }
    }

    cout << dp[n - 1] << '\n';
    return 0;
}