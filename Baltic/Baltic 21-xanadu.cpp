/*
Baltic 2021 The Xana coup
- dp[i][j][k] = Minimum number of switches to get i's subtree black,
                where j is the current colour of i and k is if we
                switched i
- Complexity: O(N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 1e9;

vector<int> graph[100001];
bool white[100001];
ll dp[100001][2][2];

void dfs(int node = 1, int parent = 0) {
    ll case_1 = 0, case_2 = 0;
    ll switch_1 = INF, switch_2 = INF;
    bool parity_1 = !white[node], parity_2 = white[node];
    for (int i : graph[node]) if (i != parent) {
        dfs(i, node);
        // Case 1: We switch node
        if (dp[i][1][0] < dp[i][1][1]) {
            case_1 += dp[i][1][0];
            switch_1 = min(switch_1, dp[i][1][1] - dp[i][1][0]);
        } else {
            case_1 += dp[i][1][1];
            switch_1 = min(switch_1, dp[i][1][0] - dp[i][1][1]);
            parity_1 ^= true;
        }
        // Case 2: We don't switch node
        if (dp[i][0][0] < dp[i][0][1]) {
            case_2 += dp[i][0][0];
            switch_2 = min(switch_2, dp[i][0][1] - dp[i][0][0]);
        } else {
            case_2 += dp[i][0][1];
            switch_2 = min(switch_2, dp[i][0][0] - dp[i][0][1]);
            parity_2 ^= true;
        }
    }
    dp[node][parity_1][1] = case_1 + 1;
    dp[node][!parity_1][1] = dp[node][parity_1][1] + switch_1;
    dp[node][parity_2][0] = case_2;
    dp[node][!parity_2][0] = dp[node][parity_2][0] + switch_2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) cin >> white[i];
    dfs();
    ll ans = min(dp[1][0][0], dp[1][0][1]);
    if (ans > n) cout << "impossible";
    else cout << ans;
    return 0;
}