/*
POI 2008 Blockade
- Whenever we remove a node, we get a bunch of connected components
- We can use biconnected components to find the sizes of these components
- Then just subtract the number of possible visits from N * (N - 1)
- Complexity: O(N + M)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll n, m;
vector<int> graph[100001], bcc_graph[200001], stck;
int low[100001], tin[100001], timer = 1, bccs = 1;
ll sz[200001], ans[200001];

void dfs(int node = 1, int parent = 0) {
    low[node] = tin[node] = timer++;
    stck.push_back(node);
    for (int i : graph[node]) if (i != parent) {
        if (tin[i]) low[node] = min(low[node], tin[i]);
        else {
            dfs(i, node);
            low[node] = min(low[node], low[i]);
            if (low[i] >= tin[node]) {
                bcc_graph[node].push_back(n + bccs);
                while (!bcc_graph[n + bccs].size() || bcc_graph[n + bccs].back() != i) {
                    bcc_graph[n + bccs].push_back(stck.back());
                    stck.pop_back();
                }
                bccs++;
            }
        }
    }
}

void dfs2(int node = 1) {
    sz[node] = (node <= n);
    for (int i : bcc_graph[node]) {
        dfs2(i);
        ans[node] += sz[i] * (sz[i] - 1);
        sz[node] += sz[i];
    }
    ans[node] += (n - sz[node]) * (n - sz[node] - 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs();
    dfs2();
    FOR(i, 1, n + 1) cout << n * (n - 1) - ans[i] << '\n';
    return 0;
}