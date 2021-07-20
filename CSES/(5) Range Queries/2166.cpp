#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 1e18;

int n, q;
ll a[200001];
pair<ll, ll> segtree[800001];

void build(int node = 1, int l = 1, int r = n) {
    if (l == r) segtree[node] = {max(0ll, a[l]), a[l]};
    else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        segtree[node].first = max(segtree[node * 2].first, segtree[node * 2].second + segtree[node * 2 + 1].first);
        segtree[node].second = segtree[node * 2].second + segtree[node * 2 + 1].second;
    }
}

void update(int pos, ll val, int node = 1, int l = 1, int r = n) {
    if (l == r) segtree[node] = {max(0ll, val), val};
    else {
        int mid = (l + r) / 2;
        if (pos > mid) update(pos, val, node * 2 + 1, mid + 1, r);
        else update(pos, val, node * 2, l, mid);
        segtree[node].first = max(segtree[node * 2].first, segtree[node * 2].second + segtree[node * 2 + 1].first);
        segtree[node].second = segtree[node * 2].second + segtree[node * 2 + 1].second;
    }
}

ll query(int x, int y, int node = 1, int l = 1, int r = n) {
    if (l > y || r < x) return -INF;
    if (l >= x && r <= y) return segtree[node].first;
    int mid = (l + r) / 2;
    return max(query(x, y, node * 2, l, mid), segtree[node * 2].second + query(x, y, node * 2 + 1, mid + 1, r));
}

ll pref(int x, int node = 1, int l = 1, int r = n) {
    if (l > x) return 0;
    if (r <= x) return segtree[node].second;
    int mid = (l + r) / 2;
    return pref(x, node * 2, l, mid) + pref(x, node * 2 + 1, mid + 1, r);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    while (q--) {
        int t, k, u;
        cin >> t >> k >> u;
        if (t == 1) update(k, u);
        else cout << query(k, u) - pref(k - 1) << '\n';
    }
    return 0;
}