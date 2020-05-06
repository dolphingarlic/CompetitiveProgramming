/*
Baltic 2016 Cities
- Since K is small, it suggests that we should do bitmask DP
- dp[mask][i] = Minimum cost such that the important cities in mask and city i are connected
- We use submask enumeration to find dp if i is not a leaf in the "spanning tree"
    - In this case, dp[mask][i] = min(dp[submask][i] + dp[mask ^ submask][i])
- Then we can do multi-source Dijkstra to handle the case where i is a leaf
- Complexity: O(3^K * M log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int important[5];
ll dp[1 << 5][100001];
bool visited[100001];
vector<pair<ll, int>> graph[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k, m;
    cin >> n >> k >> m;
    FOR(i, 0, k) cin >> important[i];
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({c, b});
        graph[b].push_back({c, a});
    }

    memset(dp, 0x3f, sizeof(dp));
    FOR(i, 0, k) dp[1 << i][important[i]] = 0;

    FOR(mask, 1, 1 << k) {
        priority_queue<pair<ll, int>> pq;
        for (int i = mask; i; i = mask & (i - 1)) {
            if ((mask ^ i) > i) continue;
            FOR(j, 1, n + 1) dp[mask][j] = min(dp[mask][j], dp[i][j] + dp[mask ^ i][j]);
        }
        
        fill(visited + 1, visited + n + 1, false);
        FOR(i, 1, n + 1) if (dp[mask][i] != 0x3f3f3f3f3f3f3f3f) pq.push({-dp[mask][i], i});

        while (pq.size()) {
            ll cost = pq.top().first;
            int curr = pq.top().second;
            pq.pop();
            if (!visited[curr]) {
                visited[curr] = true;
                for (pair<ll, int> i : graph[curr]) if (i.first - cost < dp[mask][i.second]) {
                    dp[mask][i.second] = i.first - cost;
                    pq.push({cost - i.first, i.second});
                }
            }
        }
    }

    cout << *min_element(dp[(1 << k) - 1] + 1, dp[(1 << k) - 1] + n + 1);
    return 0;
}