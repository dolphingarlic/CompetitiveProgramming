#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, a, b;
vector<int> graph[200001];
int subtree[200001];

ll ans = 0, bit[200001];
int mx_depth;
bool processed[200001];

int get_subtree_sizes(int node, int parent = 0) {
    subtree[node] = 1;
    for (int i : graph[node]) if (!processed[i] && i != parent)
        subtree[node] += get_subtree_sizes(i, node);
    return subtree[node];
}

int get_centroid(int desired, int node, int parent = 0) {
    for (int i : graph[node])
        if (!processed[i] && i != parent && subtree[i] >= desired)
            return get_centroid(desired, i, node);
    return node;
}

void update(int pos, ll val) { for (pos++; pos <= n; pos += pos & -pos) bit[pos] += val; }

ll query(int l, int r) {
    ll ans = 0;
    for (r++; r; r -= r & -r) ans += bit[r];
    for (; l; l -= l & -l) ans -= bit[l];
    return ans;
}

void get_cnt(int node, int parent, bool filling, int depth = 1) {
    if (depth > b) return;
    mx_depth = max(mx_depth, depth);
    if (filling) update(depth, 1);
    else ans += query(max(0, a - depth), b - depth);
    for (int i : graph[node]) if (!processed[i] && i != parent)
        get_cnt(i, node, filling, depth + 1);
}

void centroid_decomp(int node = 1) {
    int centroid = get_centroid(get_subtree_sizes(node) >> 1, node);
    processed[centroid] = true;
    mx_depth = 0;
    for (int i : graph[centroid]) if (!processed[i]) {
        get_cnt(i, centroid, false);
        get_cnt(i, centroid, true);
    }
    for (int i = 1; i <= mx_depth; i++) update(i, -query(i, i));
    for (int i : graph[centroid]) if (!processed[i]) centroid_decomp(i);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> a >> b;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    update(0, 1);
    centroid_decomp();
    cout << ans;
    return 0;
}