#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll gcd(ll X, ll Y) { return (Y == 0 ? X : gcd(Y, X % Y)); }

ll segtree[4004][4004], a[1001][1001];
ll n, m;

void build_y(ll node_x, ll l_x, ll r_x, ll node_y = 1, ll l_y = 1, ll r_y = m) {
    if (l_y == r_y) {
        if (l_x == r_x)
            segtree[node_x][node_y] = a[l_x][l_y];
        else
            segtree[node_x][node_y] = gcd(segtree[node_x * 2][node_y],
                                          segtree[node_x * 2 + 1][node_y]);
    } else {
        ll mid_y = (l_y + r_y) / 2;
        build_y(node_x, l_x, r_x, node_y * 2, l_y, mid_y);
        build_y(node_x, l_x, r_x, node_y * 2 + 1, mid_y + 1, r_y);
        segtree[node_x][node_y] =
            gcd(segtree[node_x][node_y * 2], segtree[node_x][node_y * 2 + 1]);
    }
}
void build_x(ll node_x = 1, ll l_x = 1, ll r_x = n) {
    if (l_x != r_x) {
        ll mid_x = (l_x + r_x) / 2;
        build_x(node_x * 2, l_x, mid_x);
        build_x(node_x * 2 + 1, mid_x + 1, r_x);
    }
    build_y(node_x, l_x, r_x);
}

ll query_y(ll y1, ll y2, ll node_x, ll node_y = 1, ll l_y = 1, ll r_y = m) {
    if (r_y < y1 || l_y > y2) return 0;
    if (r_y <= y2 && l_y >= y1) return segtree[node_x][node_y];

    ll mid_y = (l_y + r_y) / 2;
    return gcd(query_y(y1, y2, node_x, node_y * 2, l_y, mid_y),
               query_y(y1, y2, node_x, node_y * 2 + 1, mid_y + 1, r_y));
}
ll query_x(ll x1, ll x2, ll y1, ll y2, ll node_x = 1, ll l_x = 1, ll r_x = n) {
    if (r_x < x1 || l_x > x2) return 0;
    if (r_x <= x2 && l_x >= x1) return query_y(y1, y2, node_x);

    ll mid_x = (l_x + r_x) / 2;
    return gcd(query_x(x1, x2, y1, y2, node_x * 2, l_x, mid_x),
               query_x(x1, x2, y1, y2, node_x * 2 + 1, mid_x + 1, r_x));
}

void update_y(ll x, ll y, ll val, ll node_x, ll l_x, ll r_x, ll node_y = 1, ll l_y = 1, ll r_y = m) {
    if (l_y == r_y) {
        if (l_x == r_x)
            segtree[node_x][node_y] = val;
        else
            segtree[node_x][node_y] = gcd(segtree[node_x * 2][node_y],
                                          segtree[node_x * 2 + 1][node_y]);
    } else {
        ll mid_y = (l_y + r_y) / 2;
        if (y <= mid_y)
            update_y(x, y, val, node_x, l_x, r_x, node_y * 2, l_y, mid_y);
        else
            update_y(x, y, val, node_x, l_x, r_x, node_y * 2 + 1, mid_y + 1,
                     r_y);
        segtree[node_x][node_y] =
            gcd(segtree[node_x][node_y * 2], segtree[node_x][node_y * 2 + 1]);
    }
}
void update_x(ll x, ll y, ll val, ll node_x = 1, ll l_x = 1, ll r_x = n) {
    if (l_x != r_x) {
        ll mid_x = (l_x + r_x) / 2;
        if (x <= mid_x)
            update_x(x, y, val, node_x * 2, l_x, mid_x);
        else
            update_x(x, y, val, node_x * 2 + 1, mid_x + 1, r_x);
    }
    update_y(x, y, val, node_x, l_x, r_x);
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) cin >> a[i][j];
    build_x();

    ll q;
    cin >> q;
    FOR(i, 0, q) {
        char c;
        cin >> c;
        if (c == 'q') {
            ll x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << query_x(min(x1, x2), max(x1, x2), min(y1, y2), max(y1, y2))
                 << '\n';
        } else {
            ll x, y, val;
            cin >> x >> y >> val;
            update_x(x, y, val);
        }
    }
    return 0;
}
