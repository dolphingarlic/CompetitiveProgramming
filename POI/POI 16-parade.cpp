#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[200001];
// dp[0]: Max going down from i
// dp[1]: Max path with highest node i
int dp[2][200001];

void dfs(int node = 1, int parent = 0) {
    int mx1 = 1, mx2 = 1;
    for (int i : graph[node]) {
        if (i != parent) {
            dfs(i, node);
            if (dp[0][i] >= mx1) {
                mx2 = mx1;
                mx1 = dp[0][i];
            } else mx2 = max(mx2, dp[0][i]);
        }
    }
    dp[0][node] = mx1 + graph[node].size() - 2;
    dp[1][node] = mx1 + mx2 + graph[node].size() - 3;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int leaves = 0;
    FOR(i, 1, n + 1) if (graph[i].size() == 1) leaves++;

    dfs();
    int ans = 0;
    FOR(i, 1, n + 1) {
        if (graph[i].size() > 1) ans = max(ans, max(dp[1][i], dp[0][i]) + 1);
    }
    // Check if the graph is a star to minus 1
    cout << ans - (leaves == n - 1);
    return 0;
}