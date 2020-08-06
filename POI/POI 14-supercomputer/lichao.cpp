/*
POI 2014 Supercomputer
- Same as the CHT solution but using a Li-Chao tree
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Line {
    ll m, c;
    inline ll operator()(ll x) { return m * x + c; }
} segtree[4000001];

int k[1000001], mn_k = INT_MAX, mx_k = INT_MIN;
int cnt[1000001], mx_depth = 0;
vector<int> graph[1000001];

void dfs(int node = 1, int depth = 1) {
    cnt[depth]++;
    mx_depth = max(mx_depth, depth);
    for (int i : graph[node]) dfs(i, depth + 1);
}

void insert(Line seg, int node = 1, int l = mn_k, int r = mx_k) {
    if (l == r) {
        if (seg(l) > segtree[node](l)) segtree[node] = seg;
    } else {
        int mid = (l + r) / 2;
        if (segtree[node].m > seg.m) swap(segtree[node], seg);
        if (segtree[node](mid) < seg(mid)) {
            swap(segtree[node], seg);
            insert(seg, node * 2, l, mid);
        } else insert(seg, node * 2 + 1, mid + 1, r);
    }
}

ll query(ll x, int node = 1, int l = mn_k, int r = mx_k) {
    if (l == r) return segtree[node](x);
    int mid = (l + r) / 2;
    if (x < mid) return max(segtree[node](x), query(x, node * 2, l, mid));
    return max(segtree[node](x), query(x, node * 2 + 1, mid + 1, r));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < q; i++) {
        cin >> k[i];
        mn_k = min(mn_k, k[i]);
        mx_k = max(mx_k, k[i]);
    }
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        graph[p].push_back(i + 1);
    }
    dfs();

    for (int i = mx_depth, deeper = 0; i; deeper += cnt[i--]) {
        insert({i, deeper});
    }
    for (int i = 0; i < q; i++) {
        ll f = query(k[i]);
        cout << f / k[i] + (f % k[i] != 0) << " \n"[i == q - 1];
    }
    return 0;
}