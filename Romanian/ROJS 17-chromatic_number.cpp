/*
ROJS 2018 Chromatic Number
- First, use Floyd-Warshall to find APSP and the number of shortest paths between each i and j
- dp[i][k] = {SP from 1 to i, Max no. of SPs passing through k chosen nodes, No. of ways to choose the nodes}
    - We can compute dp[i][k] in a similar manner, using Floyd-Warshall
- Ans = sum(dp[i][k] with SP from 1 to N and max no. of SPs)
- Complexity: O(N^3)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

struct State {
    ll dist, paths, cnt;
} sp[301][301], dp[301][301];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, choose;
    cin >> n >> m >> choose;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++)
            dp[i][j] = sp[i][j] = {1ll << 60, 0, 0};
        sp[i][i] = {0, 1, 0};
    }
    while (m--) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        sp[a][b] = sp[b][a] = {c, 1, 0};
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) if (i != k && j != k) {
                if (sp[i][k].dist + sp[k][j].dist < sp[i][j].dist)
                    sp[i][j] = {sp[i][k].dist + sp[k][j].dist, 0, 0};
                if (sp[i][k].dist + sp[k][j].dist == sp[i][j].dist)
                    sp[i][j].paths += sp[i][k].paths * sp[k][j].paths;
            }
    
    for (int i = 1; i <= n; i++)
        dp[i][1] = {sp[1][i].dist, sp[1][i].paths, 1};

    for (int k = 2; k <= choose; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) if (i != j) {
                ll dist = dp[j][k - 1].dist + sp[j][i].dist;
                ll paths = dp[j][k - 1].paths * sp[j][i].paths;

                if (dist < dp[i][k].dist || (dist == dp[i][k].dist && paths > dp[i][k].paths))
                    dp[i][k] = {dist, paths, dp[j][k - 1].cnt};
                else if (dist == dp[i][k].dist && paths == dp[i][k].paths)
                    dp[i][k].cnt = (dp[i][k].cnt + dp[j][k - 1].cnt) % MOD;
            }

    State ans = {1ll << 60, 0, 0};
    for (int i = 1; i <= n; i++) {
        ll dist = dp[i][choose].dist + sp[i][n].dist;
        ll paths = dp[i][choose].paths * sp[i][n].paths;
        if (dist < ans.dist || (dist == ans.dist && paths > ans.paths))
            ans = {dist, paths, dp[i][choose].cnt};
        else if (dist == ans.dist && paths == ans.paths)
            ans.cnt = (ans.cnt + dp[i][choose].cnt) % MOD;
    }
    cout << ans.paths << ' ' << ans.cnt;
    return 0;
}