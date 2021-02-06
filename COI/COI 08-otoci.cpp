/*
COI 2008 Otoci
- Since N is kinda small and the TL is high, we'll use sqrt decomposition
- Let's keep two types of edges in our graph: red and blue edges
    - Red edges are the sqrt(N) most recent edges that were added
    - Blue edges are the others that were added
- If we treat blue components as nodes in a different graph joined by red edges,
  each red component has O(sqrt(N)) nodes
- We can use LCA and a BIT to find the answer for two nodes in a blue
  component in O(log N) time
- This means that we can find the answer for any two nodes in O(sqrt(N) log N) time
- Complexity: O((Q + N) sqrt(N) log N)
*/

#include <bits/stdc++.h>
using namespace std;

const int B = 666;
int to_reset;

int n, q, a[30001], l_cmp[30001], g_cmp[30001];
vector<pair<int, int>> g_graph[30001];
vector<int> l_graph[30001];
int tin[30001], tout[30001], timer, anc[30001][15], bit[30001];

inline void update(int pos, int val) { for (; pos <= n; pos += pos & -pos) bit[pos] += val; }

inline int query(int r) {
    int ans = 0;
    for (; r; r -= r & -r) ans += bit[r];
    return ans;
}

void ett_dfs(int node, int parent = 0) {
    tin[node] = timer++;
    for (int i = 1; i < 15; i++) anc[node][i] = anc[anc[node][i - 1]][i - 1];
    for (int i : l_graph[node]) if (i != parent) {
        anc[i][0] = node;
        ett_dfs(i, node);
    }
    tout[node] = timer;
}

int find(int A, int *cmp) { return (A == cmp[A]) ? A : cmp[A] = find(cmp[A], cmp); }

void onion(int A, int B, int *cmp) { cmp[find(A, cmp)] = find(B, cmp); }

void reset() {
    to_reset = B;
    for (int i = 1; i <= n; i++) {
        for (pair<int, int> j : g_graph[i]) {
            onion(j.first, j.second, l_cmp);
            l_graph[j.first].push_back(j.second);
        }
        g_graph[i].clear();
    }
    timer = 1;
    memset(tin, 0, sizeof tin);
    memset(bit, 0, sizeof bit);
    for (int i = 1; i <= n; i++) if (!tin[i]) ett_dfs(i);
    for (int i = 1; i <= n; i++) update(tin[i], a[i]), update(tout[i], -a[i]);
}

inline bool is_ancestor(int u, int v) { return tin[u] <= tin[v] && tout[u] >= tout[v]; }

inline int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    for (int i = 14; ~i; i--) if (anc[u][i] && !is_ancestor(anc[u][i], v)) u = anc[u][i];
    return anc[u][0];
}

inline int path_sum(int u, int v) {
    int l = lca(u, v);
    return query(tin[u]) + query(tin[v]) - query(tin[l]) - query(tin[anc[l][0]]);
}

void query_dfs(int node, int dest, int parent = 0, int so_far = 0) {
    int cmp = find(node, l_cmp);
    if (cmp == find(dest, l_cmp)) cout << so_far + path_sum(node, dest) << endl;
    else {
        for (pair<int, int> i : g_graph[cmp]) if (find(i.second, l_cmp) != parent)
            query_dfs(i.second, dest, cmp, so_far + path_sum(node, i.first));
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    iota(l_cmp + 1, l_cmp + n + 1, 1);
    iota(g_cmp + 1, g_cmp + n + 1, 1);
    reset();
    cin >> q;
    while (q--) {
        string s;
        int u, v;
        cin >> s >> u >> v;
        if (s[0] == 'b') {
            if (find(u, g_cmp) == find(v, g_cmp)) cout << "no" << endl;
            else {
                onion(u, v, g_cmp);
                g_graph[find(u, l_cmp)].push_back({u, v});
                g_graph[find(v, l_cmp)].push_back({v, u});
                cout << "yes" << endl;

                to_reset--;
                if (!to_reset) reset();
            }
        } else if (s[0] == 'e') {
            if (find(u, g_cmp) != find(v, g_cmp)) cout << "impossible" << endl;
            else query_dfs(u, v);
        } else {
            update(tin[u], v - a[u]);
            update(tout[u], a[u] - v);
            a[u] = v;
        }
    }
    return 0;
}
