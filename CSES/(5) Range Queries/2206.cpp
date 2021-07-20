#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int INF = 1e9;

int n, q, a[200001], segtree[800001][2];

void build(int node = 1, int l = 1, int r = n) {
    if (l == r) {
        segtree[node][0] = a[l] - l;
        segtree[node][1] = a[l] + l;
    } else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        segtree[node][0] = min(segtree[node * 2][0], segtree[node * 2 + 1][0]);
        segtree[node][1] = min(segtree[node * 2][1], segtree[node * 2 + 1][1]);
    }
}

void update(int pos, int val, int node = 1, int l = 1, int r = n) {
    if (l == r) {
        segtree[node][0] = val - l;
        segtree[node][1] = val + l;
    } else {
        int mid = (l + r) / 2;
        if (pos > mid) update(pos, val, node * 2 + 1, mid + 1, r);
        else update(pos, val, node * 2, l, mid);
        segtree[node][0] = min(segtree[node * 2][0], segtree[node * 2 + 1][0]);
        segtree[node][1] = min(segtree[node * 2][1], segtree[node * 2 + 1][1]);
    }
}

int query(int x, int y, int t, int node = 1, int l = 1, int r = n) {
    if (l > y || r < x) return INF;
    if (l >= x && r <= y) return segtree[node][t];
    int mid = (l + r) / 2;
    return min(query(x, y, t, node * 2, l, mid), query(x, y, t, node * 2 + 1, mid + 1, r));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, x;
            cin >> k >> x;
            update(k, x);
        } else {
            int k;
            cin >> k;
            cout << min(query(1, k, 0) + k, query(k, n, 1) - k) << '\n';
        }
    }
    return 0;
}