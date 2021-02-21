#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[500001];
int dp[500001], k;
double dp2[500001], ans = 0;

void dfs(int node) {
    dp[node] = 1;
    for (int i : graph[node]) {
        dfs(i);
        dp[node] += dp[i];
    }

    dp2[node] = (graph[node].size() == 0 ? INT_MAX : 0);
    for (int i : graph[node])
        dp2[node] = max(dp2[node], min(dp2[i], dp[i] / (dp[node] - 1.0)));

    if (dp[node] > k) ans = max(ans, dp2[node]);
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n >> k;
    FOR(i, 1, n) {
        int x;
        cin >> x;
        graph[x].push_back(i + 1);
    }
    dfs(1);

    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}