#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int important[5];
ll shortest[5][100001], dp[1 << 5][100001];
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

    FOR(i, 0, k) {
        priority_queue<pair<ll, int>> pq;
        pq.push({-1, important[i]});
        while (pq.size()) {
            ll cost = pq.top().first;
            int curr = pq.top().second;
            pq.pop();
            if (!shortest[i][curr]) {
                shortest[i][curr] = -cost;
                for (pair<ll, int> j : graph[curr]) pq.push({cost - j.first, j.second});
            }
        }
        FOR(j, 1, n + 1) shortest[i][j]--;
    }

    memset(dp, 0x3f, sizeof(dp));
    FOR(i, 1, n + 1) dp[0][i] = 0;
    FOR(i, 1, 1 << k) FOR(j, 0, k) if (i & (1 << j)) {
        FOR(c, 1, n + 1) dp[i][c] = min(dp[i][c], dp[i - (1 << j)][c] + shortest[j][c]);
    }

    cout << *min_element(dp[(1 << k) - 1] + 1, dp[(1 << k) - 1] + n + 1);
    return 0;
}