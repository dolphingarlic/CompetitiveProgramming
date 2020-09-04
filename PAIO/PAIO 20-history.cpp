#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, q, c[300001], to_root[300001];
vector<int> graph[300001];
int tin[300001], tout[300001], timer = 0;
pair<int, int> val[300001];
vector<pair<int, int>> seg[1200001];

void dfs(int node = 1, int parent = 0) {
    to_root[node] = to_root[parent] ^ c[node];
    tin[node] = ++timer;
    for (int i : graph[node]) if (i != parent) dfs(i, node);
    tout[node] = timer;
    val[tin[node]] = {to_root[node], node};
}

void build(int node = 1, int l = 1, int r = n) {
    if (l == r) seg[node] = {val[l]};
    else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        int lptr = 0, rptr = 0;
        int lsz = seg[node * 2].size(), rsz = seg[node * 2 + 1].size();
        while (lptr < lsz && rptr < rsz) {
            if (seg[node * 2][lptr] < seg[node * 2 + 1][rptr]) {
                seg[node].push_back(seg[node * 2][lptr++]);
            } else {
                seg[node].push_back(seg[node * 2 + 1][rptr++]);
            }
        }
        while (lptr < lsz) seg[node].push_back(seg[node * 2][lptr++]);
        while (rptr < rsz) seg[node].push_back(seg[node * 2 + 1][rptr++]);
    }
}

int query(int a, int b, int v, int node = 1, int l = 1, int r = n) {
    if (r < a || l > b || a > b) return INT_MAX;
    if (r <= b && l >= a) {
        auto lb = lower_bound(seg[node].begin(), seg[node].end(), make_pair(to_root[v], -1));
        if (lb == seg[node].end() || (*lb).first != to_root[v]) return INT_MAX;
        if ((*lb).second == v) lb++;
        if (lb == seg[node].end() || (*lb).first != to_root[v]) return INT_MAX;
        return (*lb).second;
    }
    int mid = (l + r) / 2;
    return min(query(a, b, v, node * 2, l, mid), query(a, b, v, node * 2 + 1, mid + 1, r));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs();
    build();

    while (q--) {
        int u, v;
        cin >> u >> v;
        int ans = query(tin[u] + 1, tout[u], v);
        cout << (ans == INT_MAX ? -1 : ans) << '\n';
    }
    return 0;
}