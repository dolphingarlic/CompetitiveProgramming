#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int k;
vector<pair<int, int>> graph[20001];
int dp[20001][2];

void dfs(int node) {
    priority_queue<pair<int, int>> pq;
    int sm = 0;
    for (pair<int, int> i : graph[node]) {
        dfs(i.first);
        pq.push({i.second + dp[i.first][0] - dp[i.first][1], i.first});
        sm += dp[i.first][1];
    }

    for (int i = 1; i < k && pq.size() && pq.top().first > 0; i++) {
        sm += pq.top().first;
        pq.pop();
    }
    dp[node][0] = sm;
    if (pq.size() && pq.top().first > 0) sm += pq.top().first;
    dp[node][1] = sm;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, first;
    cin >> n >> k;
    FOR(i, 1, n) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        if (i == 1) first = a;
    }

    dfs(first);
    cout << dp[first][1];
    return 0;
}