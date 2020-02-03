#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll N, K;

set<ll> graph[200001];
map<ll, ll> costs[200001];
ll subtree[200001], first_centroid;

ll A[1000001], component = 0, ans = 200001;
ll achievable[1000001],  // The lowest component we can achieve a cost of i
    min_paths[1000001];  // The minimum number of paths needed to get a cost of
                         // i

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

/////////////////////////////////////
// DFS TO FILL A FOR EACH CENTROID //
/////////////////////////////////////
void dfs(ll node, ll parent, ll cost, ll depth, bool filling) {
    if (cost > K) return;

    if (filling) {
        if (achievable[K - cost] == component)
            ans = min(ans, depth + min_paths[K - cost]);
        if (cost == K) ans = min(ans, depth);
    } else {
        if (achievable[cost] < component || depth < min_paths[cost]) {
            achievable[cost] = component;
            min_paths[cost] = depth;
        }
    }

    for (ll i : graph[node])
        if (i != parent)
            dfs(i, node, cost + costs[node][i], depth + 1, filling);
}

/////////////////////////
// PROCESS A COMPONENT //
/////////////////////////
void process(ll node) {
    get_subtree_sizes(node, 0);
    ll centroid = get_centroid(node, 0, subtree[node] / 2);

    component++;
    for (ll i : graph[centroid]) {
        dfs(i, centroid, costs[centroid][i], 1, 1);
        dfs(i, centroid, costs[centroid][i], 1, 0);
    }

    for (ll i : graph[centroid]) {
        graph[i].erase(centroid);
        graph[centroid].erase(i);
        process(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;
    FOR(i, 1, N) {
        ll a, b, c;
        cin >> a >> b >> c;
        graph[a].insert(b);
        graph[b].insert(a);
        costs[a][b] = costs[b][a] = c;
    }

    process(1);

    cout << (ans == 200001 ? -1 : ans) << '\n';
    return 0;
}
