#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll N;

set<ll> graph[50001];
ll subtree[50001], ans = 0;

////////////////////////////
// CENTROID DECOMPOSITION //
////////////////////////////
void get_subtree_sizes(ll node, ll parent) {
    subtree[node] = 1;
    for (ll i : graph[node])
        if (i != parent) {
            get_subtree_sizes(i, node);
            subtree[node] += subtree[i];
        }
}
ll get_centroid(ll node, ll parent, ll tree_size) {
    for (ll i : graph[node])
        if (i != parent && subtree[i] > tree_size)
            return get_centroid(i, node, tree_size);
    return node;
}

/////////////////////////
// PROCESS A COMPONENT //
/////////////////////////
void process(ll node, ll level = 0) {
    get_subtree_sizes(node, 0);
    ll centroid = get_centroid(node, 0, subtree[node] / 2);

    for (ll i : graph[centroid]) {
        graph[i].erase(centroid);
        process(i, level + 1);
    }
    graph[centroid].clear();

    ans = max(ans, level);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    FOR(i, 1, N) {
        ll a, b;
        cin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }

    process(1);

    cout << ans << '\n';
    return 0;
}
