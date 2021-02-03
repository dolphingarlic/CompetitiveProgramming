/*
POI 2019 Zones
- We can make any biconnected component a strongly connected component by greedily
  directing the edges in the order that we visit them in the DFS (see CSES)
- Therefore, the answer is simply the number of biconnected components in the graph
- Complexity: O(N + M)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m, bcc = 0;
char ans[1000001];
bool visited[1000001];
int tin[1000001], low[1000001], timer = 1;
vector<tuple<int, int, char>> graph[1000001];

void dfs(int node, int p_idx = 0) {
    tin[node] = low[node] = timer++;
    for (auto i : graph[node]) {
        int to, idx;
        char dir;
        tie(to, idx, dir) = i;
        if (idx == p_idx) continue;
        if (!visited[idx]) ans[idx] = dir, visited[idx] = true;
        if (tin[to]) low[node] = min(low[node], tin[to]);
        else {
            dfs(to, idx);
            low[node] = min(low[node], low[to]);
            if (low[to] > tin[node]) bcc++;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, i, '>'});
        graph[v].push_back({u, i, '<'});
    }
    for (int i = 1; i <= n; i++) if (!tin[i]) {
        dfs(i);
        bcc++;
    }
    cout << bcc << '\n';
    for (int i = 1; i <= m; i++) cout << ans[i];
    return 0;
}