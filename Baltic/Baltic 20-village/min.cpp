/*
Baltic 2020 Village (Minimum)
- The minimum distance is equal to twice the magnitude of the minimum edge cover
- To find this minimum edge cover, we do dp
    - Basically, dp[i][1/0] = Minimum edge cover of subtree i if we take/don't take
      the "parent" edge from i
- Using this information, we can then construct the edge cover and erase all
  edges not belonging to it
- We are then left with a forest
    - For each tree in the forest, do an Euler tour and do a cyclic shift to
      get the new locations of the people
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll dp[100001][2], better[100001], opt_child[100001], ans[100001];
vector<ll> graph[100001], edge_cover[100001], euler_tour;
bool visited[100001];

void dfs(ll node = 1, ll parent = 0) {
    vector<pair<ll, ll>> diff = {{INT_MAX, -1}};
    for (ll i : graph[node]) if (i != parent) {
        dfs(i, node);
        dp[node][0] += min(dp[i][0], dp[i][1]);
        diff.push_back({dp[i][1] - min(dp[i][0], dp[i][1]), i});
    }
    sort(diff.begin(), diff.end());
    dp[node][1] = dp[node][0] + 1;
    dp[node][0] += diff[0].first;
    better[node] = (dp[node][0] >= dp[node][1] ? 1 : 0);
    opt_child[node] = diff[0].second;
}

void construct(ll node = 1, ll parent = 0, ll forced = 0) {
    if (!forced) {
        for (ll i : graph[node]) if (i != parent) {
            if (i == opt_child[1]) construct(i, node, 1);
            else construct(i, node, better[i]);
        }
    } else {
        edge_cover[parent].push_back(node);
        edge_cover[node].push_back(parent);
        for (ll i : graph[node]) if (i != parent) {
            construct(i, node, better[i]);
        }
    }
}

void shift(ll node, ll parent = 0) {
    visited[node] = true;
    euler_tour.push_back(node);
    for (ll i : edge_cover[node]) if (i != parent)
        shift(i, node);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    FOR(i, 1, n) {
        ll u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs();
    construct();

    FOR(i, 1, n + 1) {
        if (!visited[i]) {
            euler_tour.clear();
            shift(i);
            FOR(j, 0, euler_tour.size()) {
                ans[euler_tour[j]] = euler_tour[(j + 1) % euler_tour.size()];
            }
        }
    }

    cout << 2 * dp[1][0] << '\n';
    FOR(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
    return 0;
}