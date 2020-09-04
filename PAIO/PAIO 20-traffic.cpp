/*
PAIO 2020 Traffic Jams
- The only edges that are ever required are the bridges in the graph
- Collapse each bridgeless component into a single node and we end up
  with a tree where the edges are bridges in the original graph
- The problem now becomes finding the distance between 2 nodes in the
  tree, which we can solve using binary jumping and DSU
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> graph[300001], bcc_graph[300001];
vector<pair<int, int>> bcc_edges;
int tin[300001], tout[300001], low[300001], timer = 0;
bool visited[300001];
int cmp[300001], anc[300001][20];

int find(int A) {
    while (A != cmp[A]) A = cmp[A], cmp[A] = cmp[cmp[A]];
    return A;
}

void onion(int A, int B) {
    cmp[find(A)] = find(B);
}

void bridge_dfs(int node = 1, int parent = 0) {
    visited[node] = true;
    tin[node] = low[node] = timer++;
    for (int i : graph[node]) if (i != parent) {
        if (visited[i]) low[node] = min(low[node], tin[i]);
        else {
            bridge_dfs(i, node);
            low[node] = min(low[node], low[i]);
            if (low[i] > tin[node]) bcc_edges.push_back({i, node});
            else onion(node, i);
        }
    }
}

void ett_dfs(int node = find(1), int parent = 0) {
    for (int i = 1; i < 20; i++) anc[node][i] = anc[anc[node][i - 1]][i - 1];
    tin[node] = timer++;
    for (int i : bcc_graph[node]) if (i != parent) {
        anc[i][0] = node;
        ett_dfs(i, node);
    }
    tout[node] = timer++;
}

bool is_ancestor(int A, int B) {
    return tin[A] <= tin[B] && tout[A] >= tout[B];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    iota(cmp + 1, cmp + n + 1, 1);
    bridge_dfs();
    for (pair<int, int> i : bcc_edges) {
        bcc_graph[find(i.first)].push_back(find(i.second));
        bcc_graph[find(i.second)].push_back(find(i.first));
    }
    timer = 0;
    ett_dfs();

    while (q--) {
        int A, B, ans = 0;
        cin >> A >> B;
        A = find(A), B = find(B);
        for (int i = 19; ~i; i--) {
            if (anc[A][i] && !is_ancestor(anc[A][i], B)) {
                ans += 1 << i;
                A = anc[A][i];
            }
            if (anc[B][i] && !is_ancestor(anc[B][i], A)) {
                ans += 1 << i;
                B = anc[B][i];
            }
        }
        if (!is_ancestor(A, B)) ans++;
        if (!is_ancestor(B, A)) ans++;
        cout << ans << '\n';
    }
    return 0;
}