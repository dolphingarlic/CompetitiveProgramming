#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Barrier {
    int a, b, c, d;
} brs[100000];
set<int> xs;
unordered_map<int, int> compressed;
ll segtree[8080808], dp1[100000], dp2[100000];
int m, n;

void update(int pos, ll val, int node = 1, int l = 1, int r = xs.size()) {
    if (l == r) segtree[node] = min(segtree[node], val);
    else {
        int mid = (l + r) / 2;
        if (pos > mid) update(pos, val, node * 2 + 1, mid + 1, r);
        else update(pos, val, node * 2, l, mid);
        segtree[node] = min(segtree[node * 2], segtree[node * 2 + 1]);
    }
}
ll query(int x, int y, int node = 1, int l = 1, int r = xs.size()) {
    if (x > r || y < l) return LLONG_MAX / m;
    else if (x <= l && y >= r) return segtree[node];
    else {
        int mid = (l + r) / 2;
        return min(query(x, y, node * 2, l, mid), query(x, y, node * 2 + 1, mid + 1, r));
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n;
    xs.insert(1);
    xs.insert(n);
    FOR(i, 0, m) {
        cin >> brs[i].a >> brs[i].b >> brs[i].c >> brs[i].d;
        xs.insert(brs[i].a); xs.insert(brs[i].b); xs.insert(brs[i].c);
    }
    int indx = 1;
    for (int i : xs) {
        compressed[i] = indx++;
    }

    fill(segtree, segtree + 4 * xs.size(), LLONG_MAX / m);
    update(1, 0);
    FOR(i, 0, m) {
        dp1[i] = query(compressed[brs[i].a], compressed[brs[i].b]) + brs[i].d;
        update(compressed[brs[i].c], dp1[i]);
    }

    fill(segtree, segtree + 4 * xs.size(), LLONG_MAX / m);
    update(xs.size(), 0);
    FOR(i, 0, m) {
        dp2[i] = query(compressed[brs[i].a], compressed[brs[i].b]) + brs[i].d;
        update(compressed[brs[i].c], dp2[i]);
    }

    ll ans = LLONG_MAX;
    FOR(i, 0, m) ans = min(ans, dp1[i] + dp2[i] - brs[i].d);
    if (ans < LLONG_MAX / m) cout << ans;
    else cout << -1;
    return 0;
}