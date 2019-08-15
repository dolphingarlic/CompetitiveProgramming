#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define MOD 1000000007
#define MAXN 100001
typedef long long ll;
using namespace std;

vector<ll> exits;
vector<pair<ll, ll>> graph[MAXN];
bool is_exit[MAXN];
ll visited[MAXN];

// Multi source Dijkstra
ll dijkstra() {
    fill(visited, visited + MAXN, 0);
    priority_queue<pair<ll, ll>> pq;  // Distance from an exit
    for (ll i : exits) {
        pq.push({0, i});
        visited[i] = 1;
    }

    while (!pq.empty()) {
        ll curr_node = pq.top().second, curr_cost = pq.top().first;
        pq.pop();

        if (visited[curr_node] == 0) {
            visited[curr_node]++;
        } else if (visited[curr_node] == 1) {
            if (curr_node == 0) return -curr_cost;
            visited[curr_node]++;
            for (pair<ll, ll> i : graph[curr_node]) pq.push({curr_cost - i.second, i.first});
        }
    }
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    ll n, m, k;
    cin >> n >> m >> k;
    FOR(i, 0, m) {
        ll a, b, l;
        cin >> a >> b >> l;
        graph[a].push_back({b, l});
        graph[b].push_back({a, l});
    }
    FOR(i, 0, k) {
        ll x;
        cin >> x;
        is_exit[x] = true;
        exits.push_back(x);
    }

    cout << dijkstra() << '\n';
    return 0;
}