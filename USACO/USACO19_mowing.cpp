/*
USACO 2019 Mowing
- dp[lis][i] = min(dp[lis - 1][j] + (x[i] - x[j]) * (y[i] - y[j]))
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Point {
    int id, x, y;
};

pair<int, int> f[200002];
vector<int> lis;
vector<vector<Point>> has_lis;
ll dp[200002];

ll eval(int id, int ax, int ay, int bx, int by) {
    return dp[id] + ll(ax - bx) * ll(ay - by);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("mowing.in");
    ofstream cout("mowing.out");
    int n, t;
    cin >> n >> t;
    for (int i = 0; i < n; i++) cin >> f[i].first >> f[i].second;
    f[n++] = {0, 0};
    f[n++] = {t, t};
    sort(f, f + n);

    for (int i = 0; i < n; i++) {
        int pos = lower_bound(lis.begin(), lis.end(), f[i].second) - lis.begin();
        if (pos == lis.size()) {
            lis.push_back(f[i].second);
            has_lis.push_back({{i, f[i].first, f[i].second}});
        } else {
            lis[pos] = f[i].second;
            has_lis[pos].push_back({i, f[i].first, f[i].second});
        }
    }

    for (int i = 1; i < has_lis.size(); i++) {
        for (Point j : has_lis[i]) {
            dp[j.id] = LLONG_MAX;
            for (Point k : has_lis[i - 1]) {
                if (k.x < j.x) {
                    if (k.y < j.y) {
                        dp[j.id] = min(dp[j.id], eval(k.id, k.x, k.y, j.x, j.y));
                    }
                } else break;
            }
        }
    }

    cout << dp[n - 1] << '\n';
    return 0;
}