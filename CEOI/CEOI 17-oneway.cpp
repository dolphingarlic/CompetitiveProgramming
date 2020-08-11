/*
CEOI 2017 One-way Streets
- Only bridges in the graph can potentially be unidirectional
- Compress the cycles into nodes. We end up with a tree with
  bridges as the edges
- The problem now becomes setting the direction of edges in a
  tree, which we can solve efficiently using a BIT
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
vector<pair<int, int>> graph[100001], compressed[100001];
pair<int, int> edges[100001];
bool visited[100001], bidir[100001], to_right[100001];
int tin[100001], tout[100001], low[100001], timer;
int cmp[100001], bit[100001];
 
int find(int A) {
    while (cmp[A] != A) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}
void onion(int A, int B) {
    cmp[find(A)] = find(B);
}
 
void bridge_dfs(int node, int parent = 0) {
    visited[node] = true;
    tin[node] = low[node] = ++timer;
    for (pair<int, int> i : graph[node]) if (i.second != parent) {
        if (visited[i.first]) low[node] = min(low[node], tin[i.first]);
        else {
            bridge_dfs(i.first, i.second);
            low[node] = min(low[node], low[i.first]);
            if (low[i.first] > tin[node]) bidir[i.second] = true;
        }
    }
}
 
void ett_dfs(int node, int parent = 0) {
    visited[node] = true;
    tin[node] = ++timer;
    for (pair<int, int> i : compressed[node]) if (i.first != parent) {
        ett_dfs(i.first, node);
    }
    tout[node] = timer;
}
 
void update(int pos, int val) {
    for (; pos <= timer; pos += (pos & (-pos))) bit[pos] += val;
}
int query(int a, int b) {
    int ans = 0;
    for (; b; b -= (b & (-b))) ans += bit[b];
    for (a--; a; a -= (a & -a)) ans -= bit[a];
    return ans;
}
 
void dir_dfs(int node, int parent = 0) {
    visited[node] = true;
    for (pair<int, int> i : compressed[node]) if (i.first != parent) {
        int weight = query(tin[i.first], tout[i.first]);
        if (!weight) bidir[abs(i.second)] = false;
        else if (weight < 0) to_right[abs(i.second)] = i.second > 0;
        else to_right[abs(i.second)] = i.second < 0;
        dir_dfs(i.first, node);
    }
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    iota(cmp + 1, cmp + n + 1, 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
        edges[i] = {u, v};
    }
    timer = 0;
    for (int i = 1; i <= n; i++) if (!visited[i]) bridge_dfs(i);
    for (int i = 1; i <= m; i++) if (!bidir[i]) onion(edges[i].first, edges[i].second);
    for (int i = 1; i <= m; i++) if (bidir[i]) {
        compressed[find(edges[i].first)].push_back({find(edges[i].second), i});
        compressed[find(edges[i].second)].push_back({find(edges[i].first), -i});
    }
    timer = 0;
    memset(visited, 0, sizeof visited);
    for (int i = 1; i <= n; i++) if (!visited[find(i)]) ett_dfs(find(i));
 
    int p;
    cin >> p;
    while (p--) {
        int a, b;
        cin >> a >> b;
        update(tin[find(a)], 1);
        update(tin[find(b)], -1);
    }
 
    memset(visited, 0, sizeof visited);
    for (int i = 1; i <= n; i++) if (!visited[find(i)]) dir_dfs(find(i));
    for (int i = 1; i <= m; i++) {
        cout << (bidir[i] ? (to_right[i] ? 'R' : 'L') : 'B');
    }
    return 0;
}