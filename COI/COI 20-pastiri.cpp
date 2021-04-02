/*
COI 2020 Pastiri
- First, root the tree
- For each sheep, find the highest node a shepherd can be at while guarding it
    - We first do multi-source BFS to find the closest sheep to each node, and
      then binary lifting to find the answer
- Let's process the sheep in order of their depths (greatest depth first)
- It's optimal to greedily assign shepherds to the highest nodes for each
  unguarded sheep as we go through the list
- We can then use DFS to mark sheep as guarded
- Complexity: O(N + K log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> graph[500001];
int sheep[500001], to_sheep[500001], depth[500001], anc[500001][19], highest[500001];
bool has_sheep[500001], guarded[500001];

void dfs(int node = 1, int parent = 0, int d = 0) {
    depth[node] = d;
    for (int i = 1; i < 19; i++) anc[node][i] = anc[anc[node][i - 1]][i - 1];

    int h = node, dist = 1;
    if (has_sheep[node])
        for (int i = 18; ~i; i--) if (dist + (1 << i) == to_sheep[anc[h][i]]) {
            dist += (1 << i);
            h = anc[h][i];
        }
    highest[node] = h;

    for (int i : graph[node]) if (i != parent) {
        anc[i][0] = node;
        dfs(i, node, d + 1);
    }
}

void guard(int node) {
    guarded[node] = true;
    for (int i : graph[node]) if (!guarded[i] && to_sheep[node] == to_sheep[i] + 1) guard(i);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    queue<int> q;
    for (int i = 1; i <= k; i++) {
        cin >> sheep[i];
        has_sheep[sheep[i]] = true;
        q.push(sheep[i]);
        to_sheep[sheep[i]] = 1;
    }
    while (q.size()) {
        int curr = q.front();
        q.pop();
        for (int i : graph[curr]) if (!to_sheep[i]) {
            to_sheep[i] = to_sheep[curr] + 1;
            q.push(i);
        }
    }
    dfs();

    vector<int> ans;
    sort(sheep + 1, sheep + k + 1, [](int A, int B) { return depth[A] > depth[B]; });
    for (int i = 1; i <= k; i++) if (!guarded[sheep[i]]) {
        int node = highest[sheep[i]];
        ans.push_back(node);
        guard(node);
    }
    cout << ans.size() << '\n';
    for (int i : ans) cout << i << ' ';
    return 0;
}
