#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
vector<ll> graph[5001];
ll mn = INT_MAX, nodes;
 
ll visited[5001];
ll bfs(ll node) {
    ll cost = 1;
    nodes = 0;
    queue<ll> q;
    fill(visited, visited + 5001, 0);
    q.push(node);
    visited[node] = 1;
    while (!q.empty()) {
        ll curr = q.front();
        nodes++;
        q.pop();
        for (auto& i : graph[curr]) {
            if (!visited[i]) {
                visited[i] = visited[curr] + 1;
                q.push(i);
                cost += visited[i];
            }
        }
    }
    return cost;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    FOR(i, 1, n + 1) {
        ll x;
        cin >> x;
        FOR(j, 0, x) {
            ll k;
            cin >> k;
            graph[k].push_back(i);
        }
    }
    FOR(i, 1, n + 1) {
        ll sum = bfs(i);
        if (nodes == n) mn = min(sum, mn);
    }
    cout << mn << '\n';
    return 0;
}