#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
using namespace std;
typedef long long ll;

struct Node {
    ll mn, sum;
    Node operator+(Node b) { return {min(b.mn, mn), b.sum + sum}; }
} segtree[808080];

ll n, q, lazy[808080], a[202020];

void push_lazy(ll node, ll l, ll r) {
    segtree[node].mn += lazy[node];
    segtree[node].sum += (r - l + 1) * lazy[node];
    if (l != r) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
}

void build(ll node = 1, ll l = 1, ll r = n) {
    if (l == r)
        segtree[node] = {a[l], a[l]};
    else {
        ll mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }
}

void update(ll x, ll y, ll val, ll node = 1, ll l = 1, ll r = n) {
    if (lazy[node]) push_lazy(node, l, r);
    if (r < x || l > y) return;
    if (r <= y && l >= x) {
        lazy[node] = val;
        push_lazy(node, l, r);
    } else {
        ll mid = (l + r) / 2;
        update(x, y, val, node * 2, l, mid);
        update(x, y, val, node * 2 + 1, mid + 1, r);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }
}

ll query_sum(ll x, ll y, ll node = 1, ll l = 1, ll r = n) {
    if (lazy[node]) push_lazy(node, l, r);
    if (r < x || l > y) return 0;
    if (r <= y && l >= x) return segtree[node].sum;
    ll mid = (l + r) / 2;
    return query_sum(x, y, node * 2, l, mid) +
           query_sum(x, y, node * 2 + 1, mid + 1, r);
}
ll query_min(ll x, ll y, ll node = 1, ll l = 1, ll r = n) {
    if (lazy[node]) push_lazy(node, l, r);
    if (r < x || l > y) return LLONG_MAX;
    if (r <= y && l >= x) return segtree[node].mn;
    ll mid = (l + r) / 2;
    return min(query_min(x, y, node * 2, l, mid),
               query_min(x, y, node * 2 + 1, mid + 1, r));
}

int main() {
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);

    cin >> n >> q;
    FOR(i, 1, n + 1) cin >> a[i];
    build();
    while (q--) {
        char c;
        cin >> c;
        if (c == 'M') {
            ll x, y;
            cin >> x >> y;
            cout << query_min(x, y) << '\n';
        } else if (c == 'S') {
            ll x, y;
            cin >> x >> y;
            cout << query_sum(x, y) << '\n';
        } else {
            ll x, y, val;
            cin >> x >> y >> val;
            update(x, y, val);
        }
    }
    return 0;
}