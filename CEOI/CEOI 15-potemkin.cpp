/*
CEOI 2016 Potemkin Cycle
- Let each edge (u, v) represent two nodes (uv) and (vu) in graph H
- There is an edge between (uv) and (vw) in H iff (uw) doesn't exist
    - This means that there are no cycles of length 3 in H
    - We can construct H in O(NR) time
- An answer exists iff a cycle exists in H; run DFS to find a cycle
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int u[200001], v[200001], adj[1001][1001];
vector<int> graph[200001], stck;
bool visited[200001], active[200001];

void dfs(int node, int parent) {
    if (active[node]) {
        while (stck.back() != node) {
            cout << v[stck.back()] << ' ';
            stck.pop_back();
        }
        cout << v[node];
        exit(0);
    }
    if (visited[node]) return;

    stck.push_back(node);
    visited[node] = active[node] = true;
    for (int i : graph[node]) if (i != parent) dfs(i, node);
    stck.pop_back();
    active[node] = false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, r;
    cin >> n >> r;
    for (int i = 1; i <= r; i++) {
        cin >> u[i] >> v[i];
        u[i + r] = v[i], v[i + r] = u[i];
        adj[u[i]][v[i]] = i, adj[v[i]][u[i]] = i + r;
    }

    for (int i = 1; i <= 2 * r; i++) {
        for (int j = 1; j <= n; j++) if (j != u[i]) {
            if (adj[v[i]][j] && adj[u[i]][j] == 0)
                graph[i].push_back(adj[v[i]][j]);
        }
    }

    for (int i = 1; i <= 2 * r; i++) if (!visited[i]) dfs(i, i);
    cout << "no";
    return 0;
}
