#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

vector<int> graph[500001];
int dp[500001], k;
double dp2[500001], ans = 0;

void dfs(int node) {
    dp[node] = 1;
    dp2[node] = 0;
    for (int i : graph[node]) {
        dfs(i);
        dp[node] += dp[i];
        dp2[node] = max(dp2[node], dp2[i]);
    }
    if (dp[node] > k) {
        for (int i : graph[node]) {
            if (dp[i] > k) dp2[node] = max(dp2[node], dp2[i]);
            else dp2[node] = max(dp2[node], dp[i] / (dp[node] - 1.0));
        }
    } else {
        dp2[node] = 0;
    }
    // cout << dp2[node] << endl;
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

    cout << fixed << setprecision(10) << dp2[1] << '\n';
    return 0;
}