#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Node {
    ll ans, pref, suff, tot;
    Node operator+(Node b) {
        return {max(max(ans, b.ans), suff + b.pref), max(pref, b.pref + tot),
                max(b.suff, suff + b.tot), tot + b.tot};
    }
    Node operator+(ll b) { return {ans + b, pref + b, suff + b, tot + b}; }
} segtree[808080];

ll n, m, k, d;

void build(ll node = 1, ll l = 1, ll r = n) {
    if (l == r)
        segtree[node] = {-k, -k, -k, -k};
    else {
        ll mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }
}
void update(ll pos, ll val, ll node = 1, ll l = 1, ll r = n) {
    if (l == r)
        segtree[node] = segtree[node] + val;
    else {
        ll mid = (l + r) / 2;
        if (pos > mid)
            update(pos, val, node * 2 + 1, mid + 1, r);
        else
            update(pos, val, node * 2, l, mid);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k >> d;
    build();
    ll lim = k * d;

    FOR(i, 0, m) {
        ll a, b;
        cin >> a >> b;
        update(a, b);
        cout << (segtree[1].ans > lim ? "NIE\n" : "TAK\n");
    }
    return 0;
}