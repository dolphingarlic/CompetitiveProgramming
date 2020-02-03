#include <bits/stdc++.h>
using namespace std;

int n, k, a, c;
bool visited[103][103][53];
int dp[103][103][53];
vector<pair<int, int>> graph[103];
int T[103], D[103], s[103], b[103];
int saving[103][103];
int totalCost;

void preprocess(int node, int d) {
    D[node] = d;
    for (pair<int, int> i : graph[node]) {
        preprocess(i.first, d + i.second);
        T[node] += T[i.first];
        totalCost += T[i.first] * i.second;
    }

    if (graph[node].size()) s[node] = graph[node][0].first;
    for (int i = 1; i < graph[node].size(); i++)
        b[graph[node][i - 1].first] = graph[node][i].first;
}

int dfs(int i, int j, int k) {
    if (i == 0 || k == 0) return 0;

    if (!visited[i][j][k]) {
        visited[i][j][k] = 1;
        int x = 0, r;
        for (r = 0; r < k; r++)
            x = max(x, dfs(s[i], i, r) + dfs(b[i], j, k - r - 1));
        x += saving[i][j];

        for (r = 0; r <= k; r++)
            x = max(x, dfs(s[i], j, r) + dfs(b[i], j, k - r));

        dp[i][j][k] = x;
    }
    return dp[i][j][k];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> T[i] >> a >> c;
        graph[a].push_back({i, c});
    }

    preprocess(0, 0);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++) saving[i][j] = T[i] * (D[i] - D[j]);

    int ans = totalCost - dfs(s[0], 0, k);
    cout << ans;
    return 0;
}