/*
Balkan 2012 Shortest Paths
- First, run Dijkstra from A and B. Construct the shortest path tree rooted at A and force
  the lucky path to be on it
    - Notice how lca(X, B) is a node on the lucky path for each X
- If we remove an edge, the shortest path tree splits into 2 smaller trees
    - This means the shortest path must be of the form A->U->V->B where
      U and V are connected by 1 edge and U and V are in separate smaller trees
- Notice how for each edge (U, V, C), it is only valid for removed edges between lca(U, B) and lca(V, B)
    - This means we just update all nodes between those 2 nodes to be the minimum A->U + U->V + V->C
- Complexity: O(N^2 + M log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Edge {
    int u, v;
    ll c;
} edges[200000];

bool operator<(Edge a, Edge b) {
    if (a.c == b.c) {
        if (a.u == b.u) return a.v < b.v;
        return a.u < b.u;
    }
    return a.c < b.c;
}

vector<pair<int, ll>> graph[2001];
vector<int> sp_tree[2001];
int sp[2001], lca[2001];
ll from_a[2001], from_b[2001], ans[2001];
int par[2001], depth[2001];

void dijkstra(int source, ll *dist) {
    priority_queue<tuple<ll, int, int>> pq;
    pq.push({-1, source, 0});
    while (pq.size()) {
        int curr, parent;
        ll cost;
        tie(cost, curr, parent) = pq.top();
        pq.pop();
        if (!dist[curr]) {
            par[curr] = parent;
            dist[curr] = -cost;
            for (pair<int, ll> i : graph[curr]) pq.push({cost - i.second, i.first, curr});
        }
    }
}

void dfs(int node) {
    for (int i : sp_tree[node]) {
        depth[i] = depth[node] + 1;
        dfs(i);
    }
}

int find_lca(int a, int b) {
    while (depth[a] > depth[b]) a = par[b];
    while (depth[b] > depth[a]) b = par[b];
    while (a != b) a = par[a], b = par[b];
    return a;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b, k;
    cin >> n >> m >> a >> b;
    FOR(i, 0, m) {
        cin >> edges[i].u >> edges[i].v >> edges[i].c;
        edges[i + m] = {edges[i].v, edges[i].u, edges[i].c};
        graph[edges[i].u].push_back({edges[i].v, edges[i].c});
        graph[edges[i].v].push_back({edges[i].u, edges[i].c});
    }

    dijkstra(b, from_b);
    dijkstra(a, from_a);

    cin >> k;
    FOR(i, 0, k) {
        cin >> sp[i];
        if (i) par[sp[i]] = sp[i - 1];
    }

    FOR(i, 1, n + 1) if (par[i]) sp_tree[par[i]].push_back(i);
    dfs(a);
    FOR(i, 1, n + 1) lca[i] = find_lca(i, b);

    memset(ans, 0x3f, sizeof(ans));
    FOR(i, 0, 2 * m) {
        if (par[edges[i].u] == edges[i].v || par[edges[i].v] == edges[i].u) continue;
        int x = find(sp, sp + k, lca[edges[i].u]) - sp, y = find(sp, sp + k, lca[edges[i].v]) - sp;
        FOR(j, x, y) ans[j] = min(ans[j], from_a[edges[i].u] + from_b[edges[i].v] + edges[i].c - 2);
    }

    FOR(i, 0, k - 1) cout << (ans[i] == 0x3f3f3f3f3f3f3f3f ? -1 : ans[i]) << '\n';
    return 0;
}