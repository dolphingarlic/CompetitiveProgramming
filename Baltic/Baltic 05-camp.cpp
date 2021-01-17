/*
Baltic 2005 Camouflage Camp
- Just test each location and characteristic in O(RCK) time
- Use 2D prefix sums to query range sums quickly
- Also, break early when you're sure that a location certainly can't be the optimal one.
*/

#include <bits/stdc++.h>
using namespace std;

int pref[1001][1001];
pair<int, int> loc[1001], sz[1001];
bool arr[1001], alt[1001];
pair<int, pair<int, int>> ans = {INT_MAX, {0, 0}};

int tot_h(int x1, int y1, int x2, int y2) {
    return pref[x2][y2] + pref[x1 - 1][y1 - 1] - pref[x2][y1 - 1] - pref[x1 - 1][y2];
}

int check(int x, int y, int k) {
    int ret = 0;
    for (int i = 1; i <= k; i++) {
        int h_1 = tot_h(x - 1 + loc[i].first, y - 1 + loc[i].second, x - 1 + loc[i].first + sz[i].first - 1, y - 1 + loc[i].second + sz[i].second - 1);
        int h_2 = tot_h(x - 1 + loc[i].first + arr[i] * sz[i].first, y - 1 + loc[i].second + (!arr[i]) * sz[i].second, x - 1 + loc[i].first + sz[i].first - 1 + arr[i] * sz[i].first, y - 1 + loc[i].second + sz[i].second - 1 + (!arr[i]) * sz[i].second);
        if ((h_1 >= h_2) ^ alt[i]) ret++;
        if (ret >= ans.first) return INT_MAX;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        cin >> pref[i][j];
        pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }
    int l, w, k;
    cin >> l >> w >> k;
    for (int i = 1; i <= k; i++)
        cin >> loc[i].first >> loc[i].second >> sz[i].first >> sz[i].second >> arr[i] >> alt[i];
    for (int i = 1; i <= n - l + 1; i++) for (int j = 1; j <= m - w + 1; j++) ans = min(ans, {check(i, j, k), {i, j}});
    cout << ans.second.first << ' ' << ans.second.second << '\n' << k - ans.first;
    return 0;
}
