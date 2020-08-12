/*
Baltic 2017 Railway
- Just use a BIT and binary lifting to increment each edge on each spanning tree
- Complexity: O(M log^2 N)
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, k;
vector<pair<int, int>> graph[100001];
int tin[100001], tout[100001], timer = 0, anc[100001][20], p_edge[100001];
int chosen[50001], bit[100001];

void dfs(int node = 1, int parent = 0) {
    tin[node] = ++timer;
    for (int i = 1; i < 20; i++) anc[node][i] = anc[anc[node][i - 1]][i - 1];
    for (pair<int, int> i : graph[node]) if (i.first != parent) {
        anc[i.first][0] = node;
        p_edge[i.first] = i.second;
        dfs(i.first, node);
    }
    tout[node] = timer;
}

bool is_ancestor(int a, int b) {
    return (tin[a] <= tin[b] && tout[a] >= tout[b]);
}

int lca(int a, int b) {
    if (is_ancestor(a, b)) return a;
    for (int i = 19; ~i; i--) {
        if (anc[a][i] && !is_ancestor(anc[a][i], b)) a = anc[a][i];
    }
    return anc[a][0];
}

void update(int pos, int val) {
    for (; pos <= n; pos += pos & (-pos)) bit[pos] += val;
}

int query(int a, int b) {
    int ans = 0;
    for (; b; b -= b & (-b)) ans += bit[b];
    for (a--; a; a -= a & (-a)) ans -= bit[a];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back({b, i});
        graph[b].push_back({a, i});
    }
    dfs();
    while (m--) {
        int s, l;
        cin >> s;
        for (int i = 0; i < s; i++) cin >> chosen[i];
        sort(chosen, chosen + s, [](int A, int B) { return tin[A] < tin[B]; });
        chosen[s] = chosen[0];
        for (int i = 0; i < s; i++) {
            int l = lca(chosen[i], chosen[i + 1]);
            update(tin[chosen[i]], 1);
            update(tin[chosen[i + 1]], 1);
            update(tin[l], -2);
        }
    }
    vector<int> ans;
    for (int i = 2; i <= n; i++)
        if (query(tin[i], tout[i]) >= 2 * k)
            ans.push_back(p_edge[i]);
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int i : ans) cout << i << ' ';
    return 0;
}