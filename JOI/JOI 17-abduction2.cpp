/*
JOI 2017 Abduction 2
- dp[x][y][dir] = Maximum distance we can achieve if we leave intersection (x, y) with direction dir
    - We store this in a map because why not
- Let nxt[x][y][dir] = The next intersection we turn at if we leave intersection (x, y) with direction dir
    - We can find this using binary jumping + a sparse table
- dp[x][y][dir] = (Dist to nxt[x][y][dir]) + max(dp[nxt[x][y][dir]][The other two directions])
    - We can compute this using a DFS
- We will only visit O(4 * (H + W)) states for each query
    - Consider the "critical streets" i.e. the sequence of streets that form strictly increasing
      sequences on either side of the starting streets
    - Each horizontal critical street can only turn onto at most 2 vertical critical streets and vice versa
    - This means there are at most 2 * (H + W) intersections that we consider
    - Each intersection also only has 2 possible turning directions
    - Therefore, each DFS visits O(4 * (H + W)) states
- Complexity: O(4Q * (H + W) * log HW)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

map<tuple<int, int, int>, ll> dp;
int n, m, h[50001][16], v[50001][16];

ll dfs(int x, int y, int dir) {
    if (dp.count({x, y, dir})) return dp[{x, y, dir}];
    ll &ans = dp[{x, y, dir}];
    if (dir & 1) { // Up or down (x changes)
        int sign = dir - 2;
        int nxt_x = x;
        for (int i = 15; ~i; i--) {
            int tmp_x = nxt_x + (1 << i) * sign - sign;
            if (tmp_x < 1 || tmp_x > n) continue;
            if ((sign == 1 ? h[nxt_x][i] : h[tmp_x][i]) > v[y][0]) continue;
            nxt_x = tmp_x + sign;
        }
        if (nxt_x < 1 || nxt_x > n) return ans = abs(nxt_x - sign - x);
        return ans = abs(nxt_x - x) + max(dfs(nxt_x, y, 0), dfs(nxt_x, y, 2));
    } else { // Left or right (y changes)
        int sign = dir - 1;
        int nxt_y = y;
        for (int i = 15; ~i; i--) {
            int tmp_y = nxt_y + (1 << i) * sign - sign;
            if (tmp_y < 1 || tmp_y > m) continue;
            if ((sign == 1 ? v[nxt_y][i] : v[tmp_y][i]) > h[x][0]) continue;
            nxt_y = tmp_y + sign;
        }
        if (nxt_y < 1 || nxt_y > m) return ans = abs(nxt_y - sign - y);
        return ans = abs(nxt_y - y) + max(dfs(x, nxt_y, 1), dfs(x, nxt_y, 3));
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) cin >> h[i][0];
    for (int i = 1; i <= m; i++) cin >> v[i][0];
    for (int j = 1; j < 16; j++) {
        for (int i = 1; i <= n - (1 << j) + 1; i++) {
            h[i][j] = max(h[i][j - 1], h[i + (1 << j - 1)][j - 1]);
        }
        for (int i = 1; i <= m - (1 << j) + 1; i++) {
            v[i][j] = max(v[i][j - 1], v[i + (1 << j - 1)][j - 1]);
        }
    }
    while (q--) {
        int x, y;
        cin >> x >> y;
        ll ans = 0;
        if (x < n) ans = max(ans, dfs(x + 1, y, 3) + 1);
        if (y < m) ans = max(ans, dfs(x, y + 1, 2) + 1);
        if (x > 1) ans = max(ans, dfs(x - 1, y, 1) + 1);
        if (y > 1) ans = max(ans, dfs(x, y - 1, 0) + 1);
        cout << ans << '\n';
    }
    return 0;
}