#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

vector<pair<ll, ll>> graph[100001];
ll du[100001], dv[100001], ds[100001], dp[2][100001], ans;
bool visited[100001];

void dijkstra1(ll start, ll arr[]) {
    fill(visited, visited + 100001, false);

    priority_queue<pair<ll, ll>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        ll c, node;
        tie(c, node) = pq.top();
        pq.pop();

        if (!visited[node]) {
            arr[node] = -c;
            visited[node] = true;
            for (auto& i : graph[node]) pq.push({c - i.second, i.first});
        }
    }
}

void dijkstra2(ll start, ll end) {
    FOR(i, 0, 2) fill(dp[i], dp[i] + 100001, LLONG_MAX / 2);
    fill(visited, visited + 100001, false);

    priority_queue<pair<ll, pair<ll, ll>>> pq;
    pq.push({0, {start, 0}});
    dp[0][0] = dp[1][0] = LLONG_MAX/ 2;
    while (!pq.empty()) {
        ll c, node, par;
        pair<ll, ll> p;
        tie(c, p) = pq.top();
        tie(node, par) = p;
        pq.pop();

        if (!visited[node]) {
            visited[node] = true;
            ds[node] = -c;
            dp[0][node] = min(du[node], dp[0][par]);
            dp[1][node] = min(dv[node], dp[1][par]);
            for (auto& i : graph[node]) pq.push({c - i.second, {i.first, node}});
        } else if (-c == ds[node]) {
            if (min(du[node], dp[0][par]) + min(dv[node], dp[1][par]) <= dp[0][node] + dp[1][node]) {
                dp[0][node] = min(du[node], dp[0][par]);
                dp[1][node] = min(dv[node], dp[1][par]);
            }
        }
    }

    ans = min(ans, dp[0][end] + dp[1][end]);
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    ll n, m, s, t, u, v;
    cin >> n >> m >> s >> t >> u >> v;
    FOR(i, 0, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }

    dijkstra1(u, du);
    dijkstra1(v, dv);

    ans = du[v];

    dijkstra2(s, t);
    dijkstra2(t, s);

    cout << ans << '\n';
    return 0;
}