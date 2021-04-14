#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, k, s, ans = 0, dp[100001];
vector<int> graph[100001];

void dfs(int node) {
    dp[node] = 1;
    for (int i : graph[node]) {
        dfs(i);
        if (dp[i] == k) ans++;
        else dp[node] = max(dp[node], dp[i] + 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k >> s;
    if (s != 1) ans++;
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        graph[p].push_back(i);
    }
    for (int i : graph[1]) dfs(i);
    cout << ans;
    return 0;
}
