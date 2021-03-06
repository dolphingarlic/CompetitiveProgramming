/*
APIO 2013 Toll
- Firstly, notice that there will always be at least N - K edges that are present in
  the MST for any valid assignment of costs to the new roads
    - Call these edges the "mandatory edges"
- If we set the costs of the new roads to 0, then we can use Kruskal's to find the
  mandatory edges
- The use of each new road is determined by the cost of exactly one existing road
    - Call this set of roads the "critical roads"
- Since they're always present, we can compress the components in the graph with only
  mandatory edges into single nodes, adding the number of people in each component
- We're therefore left with at most K + 1 compressed nodes and K critical roads
- By iterating over all possible subsets of new roads that we can force people to
  use (e.g. using a bitmask), we can greedily assign costs to the new roads and take
  the best result
- Complexity: O(M log M + K * 2^K)
*/

#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
typedef long long ll;
using namespace std;

int n, m, k;
int u[300021], v[300021];
ll c[300021], p[100001];

int cmp1[100001], cmp2[100001], cmp3[100001];
inline int find(int A, int *cmp) { return (A == cmp[A] ? A : cmp[A] = find(cmp[A], cmp)); }
inline void onion(int A, int B, int *cmp) { cmp[find(A, cmp)] = find(B, cmp); }

vector<int> compressed;
vector<pair<int, ll>> graph[100001];
int root;
vector<tuple<ll, int, int>> critical;
int tin[100001], tout[100001], timer;
pair<int, int> par[100001];

void dfs(int node, int parent = 0) {
    cmp3[node] = node;
    tin[node] = timer++;
    for (int i = 0; i < graph[node].size(); i++) if (graph[node][i].first != parent) {
        dfs(graph[node][i].first, node);
        par[graph[node][i].first] = {node, i};
    }
    tout[node] = timer;
}

inline bool is_ancestor(int A, int B) { return tin[A] <= tin[B] && tout[A] >= tout[B]; }

pair<ll, ll> calc(int node, int parent = 0) {
    pair<ll, ll> ans = {0, p[node]};
    for (pair<int, ll> i : graph[node]) if (i.first != parent) {
        pair<ll, ll> tmp = calc(i.first, node);
        ans.first += tmp.first + tmp.second * i.second;
        ans.second += tmp.second;
    }
    return ans;
}

ll check(int mask) {
    // Reset the graph and the DSU
    for (int i : compressed) graph[i].clear(), cmp2[i] = i;

    // Onion stuff based on mask, and construct some edges in the graph
    for (int i = 1; i <= k; i++) if (mask & (1 << i - 1)) {
        if (find(u[m + i], cmp2) == find(v[m + i], cmp2)) return 0;
        graph[u[m + i]].push_back({v[m + i], 1});
        graph[v[m + i]].push_back({u[m + i], 1});
        onion(u[m + i], v[m + i], cmp2);
    }

    vector<tuple<ll, int, int>> to_assign;
    for (auto& i : critical) {
        if (find(get<1>(i), cmp2) == find(get<2>(i), cmp2)) to_assign.push_back(i);
        else {
            // Add an edge to the graph
            graph[get<1>(i)].push_back({get<2>(i), 0});
            graph[get<2>(i)].push_back({get<1>(i), 0});
            onion(get<1>(i), get<2>(i), cmp2);
        }
    }

    // Assign weights
    dfs(root);
    for (auto& i : to_assign) {
        get<1>(i) = find(get<1>(i), cmp3);
        while (!is_ancestor(get<1>(i), get<2>(i))) {
            if (graph[par[get<1>(i)].first][par[get<1>(i)].second].second)
                graph[par[get<1>(i)].first][par[get<1>(i)].second].second = get<0>(i);
            onion(get<1>(i), par[get<1>(i)].first, cmp3);
            get<1>(i) = find(get<1>(i), cmp3);
        }
        get<2>(i) = find(get<2>(i), cmp3);
        while (!is_ancestor(get<2>(i), get<1>(i))) {
            if (graph[par[get<2>(i)].first][par[get<2>(i)].second].second)
                graph[par[get<2>(i)].first][par[get<2>(i)].second].second = get<0>(i);
            onion(get<2>(i), par[get<2>(i)].first, cmp3);
            get<2>(i) = find(get<2>(i), cmp3);
        }
    }

    return calc(root).first;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) cin >> u[i] >> v[i] >> c[i];
    for (int i = 1; i <= k; i++) cin >> u[m + i] >> v[m + i];
    for (int i = 1; i <= n; i++) cin >> p[i];

    // Find the mandatory edges and collapse components together
    vector<tuple<ll, int, int>> edges;
    for (int i = 1; i <= m + k; i++) edges.push_back({c[i], u[i], v[i]});
    sort(edges.begin(), edges.end());
    iota(cmp1 + 1, cmp1 + n + 1, 1);
    iota(cmp2 + 1, cmp2 + n + 1, 1);
    for (auto& i : edges) {
        if (find(get<1>(i), cmp1) != find(get<2>(i), cmp1)) {
            if (get<0>(i)) {
                p[find(get<2>(i), cmp2)] += p[find(get<1>(i), cmp2)];
                onion(get<1>(i), get<2>(i), cmp2);
            }
            onion(get<1>(i), get<2>(i), cmp1);
        }
    }

    // Find the K + 1 component parents and the root after compression
    for (int i = 1; i <= n; i++) {
        cmp1[i] = cmp2[i];
        if (i == cmp2[i]) compressed.push_back(i);
    }
    root = find(1, cmp2);
    // Find the K "critical" edges
    for (auto& i : edges) {
        if (get<0>(i) && find(get<1>(i), cmp1) != find(get<2>(i), cmp1)) {
            critical.push_back(i);
            onion(get<1>(i), get<2>(i), cmp1);
        }
    }
    // Re-index
    for (int i = 1; i <= k; i++) u[m + i] = find(u[m + i], cmp2), v[m + i] = find(v[m + i], cmp2);
    for (auto& i : critical) get<1>(i) = find(get<1>(i), cmp2), get<2>(i) = find(get<2>(i), cmp2);

    // Test each subset of edges
    ll ans = 0;
    for (int mask = 1; mask < (1 << k); mask++) ans = max(ans, check(mask));
    cout << ans;
    return 0;
}
