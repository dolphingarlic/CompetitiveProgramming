#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MOD = 1e9 + 7;

vector<int> graph[20];
int dp[1 << 20][20];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u - 1].push_back(v - 1);
    }
    dp[1][0] = 1;
    for (int mask = 1; mask < (1 << n); mask++)
        for (int i = 0; i < n; i++) if (mask & (1 << i)) {
            for (int j : graph[i]) {
                dp[mask ^ (1 << j)][j] += dp[mask][i];
                if (dp[mask ^ (1 << j)][j] >= MOD) dp[mask ^ (1 << j)][j] -= MOD;
            }
        }
    cout << dp[(1 << n) - 1][n - 1];
    return 0;
}