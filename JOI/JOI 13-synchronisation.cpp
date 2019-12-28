/*
JOI 2013 Synchronisation
- In this problem, we essentially want to synchronise data between connected components
  in a forest. We need to support 4 types of queries:
    - Set all nodes in a connected component to have value x
    - Find the value in some node
    - Split a connected component
    - Join 2 connected components

- 1) How do we sync data without actually storing the computers that have synced?
    - Let u and v be connected, where u is the parent of v
    - For each node v, store a value info[v] which denotes the amount of info in it
    - Let last_sync[v] be the amount of data that was common between u and v
      the last time they synced
    - Clearly, the new amount of data (newval) will be info[u] + info[v] - last_sync[v]
      if we connect u and v
    - Simply set info[u] = info[v] = last_sync[v] = newval
- 2) How can we represent connected components?
    - Root the tree arbitrarily
    - Each connected component must have a single lowest ancestor
    - We can do all operations for that connected component on that ancestor
    - We can find it in O(log^2 N) with DFS, binary lifting, and a Fenwick tree
        - First find the dfs order of the nodes (i.e. find tin and tout)
        - Update a node in the Fenwick tree to be +1 if it has an active edge to its parent
        - Notice that we can do path queries if we update tin[node] -> +1 and tout[node] -> -1
        - Let query(x) be the sum from the Fenwick tree from 1 to x
        - u is an ancestor of v iff query(u) == query(v)
        - Thus we can use binary lifting to find the lowest ancestor of a component
- 3) How can we process a split/union?
    - Let u and v be the edge concerned, where u is the parent of v
    - When we union 2 components, just apply 1) but instead of just u, update lowest_ancestor(u)
    - When we split a component, v becomes its component's lowest ancestor, so just update info[v]
      and last_sync[v] accordingly
    - Also, update the Fenwick tree for both events
        - tin[node] -> +1, tout[node] -> -1 for unions
        - tin[node] -> 0, tout[node] -> 0 for splits

- Complexity: O(N log^2 N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m, q;
bool active[100001];
vector<int> graph[100001];
pair<int, int> edges[200001];

int info[100001], last_sync[100001];

// DFS order
int timer = 1, tin[100001], tout[100001];
// Binary lifting parents
int anc[100001][20];

void dfs(int node = 1, int parent = 0) {
    anc[node][0] = parent;
    for (int i = 1; i < 20 && anc[node][i - 1]; i++) {
        anc[node][i] = anc[anc[node][i - 1]][i - 1];
    }

    info[node] = 1;

    tin[node] = timer++;
    for (int i : graph[node]) if (i != parent) dfs(i, node);
    tout[node] = timer;
}

// Fenwick tree
int bit[100001];

void update(int pos, int val) { for (; pos <= n; pos += (pos & (-pos))) bit[pos] += val; }

int query(int pos) {
    int ans = 0;
    for (; pos; pos -= (pos & (-pos))) ans += bit[pos];
    return ans;
}

// Binary lifting
int find_ancestor(int node) {
    int lca = node;
    for (int i = 19; ~i; i--) {
        if (anc[lca][i] && query(tin[anc[lca][i]]) == query(tin[node])) lca = anc[lca][i];
    }
    return lca;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    FOR(i, 1, n) {
        cin >> edges[i].first >> edges[i].second;
        graph[edges[i].first].push_back(edges[i].second);
        graph[edges[i].second].push_back(edges[i].first);
    }
    dfs();

    FOR(i, 1, n + 1) {
        update(tin[i], -1);
        update(tout[i], 1);
    }

    while (m--) {
        int x;
        cin >> x;
        int u = edges[x].first, v = edges[x].second;
        if (anc[u][0] == v) swap(u, v);

        if (active[x]) {
            info[v] = last_sync[v] = info[find_ancestor(u)];
            update(tin[v], -1);
            update(tout[v], 1);
        } else {
            info[find_ancestor(u)] += info[v] - last_sync[v];
            update(tin[v], 1);
            update(tout[v], -1);
        }
        active[x] = !active[x];
    }

    while (q--) {
        int x;
        cin >> x;
        cout << info[find_ancestor(x)] << '\n';
    }
    return 0;
}