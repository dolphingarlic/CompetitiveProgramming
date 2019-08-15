#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[1000000], dp2[1000000], totsum = 0, ans = LLONG_MAX, city;
vector<ll> graph[1000000];
pair<ll, ll> dp1[1000000];

void dfs(ll node, ll parent = -1) {
    dp1[node] = {0, a[node]};
    for (ll i : graph[node]) {
        if (i == parent) continue;
        dfs(i, node);
        dp1[node].first = max(dp1[node].first, dp1[i].second);
        dp1[node].second += dp1[i].second;
    }
    dp2[node] = totsum - dp1[node].second;
    if (ans > max(dp1[node].first, dp2[node])) ans = max(dp1[node].first, dp2[node]), city = node;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    FOR(i, 0, n) {
        cin >> a[i];
        totsum += a[i];
    }
    FOR(i, 0, n - 1) {
        ll x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(0);
    cout << city << '\n';
    return 0;
}