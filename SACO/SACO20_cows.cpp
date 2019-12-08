#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define x first
#define y second
using namespace std;
typedef long long ll;

ll n, q, t = -1;
vector<ll> graph[100001];
pair<ll, ll> bounds[100001];
ll speed[100001];
pair<ll, pair<ll, ll>> len[100001];

pair<ll, ll> segtree[404040]; // Length of path to root and min speed
ll lazy[404040];

void push_lazy(ll node, ll l, ll r) {
    segtree[node].x += lazy[node];
    if (l != r) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
}
void update_speed(ll pos, ll val, ll node = 1, ll l = 1, ll r = n) {
    push_lazy(node, l, r);
    if (l == r) segtree[node].y = val;
    else {
        ll mid = (l + r) / 2;
        if (pos > mid) update_speed(pos, val, node * 2 + 1, mid + 1, r);
        else update_speed(pos, val, node * 2, l, mid);
        segtree[node].y = min(segtree[node * 2].y, segtree[node * 2 + 1].y);
    }
}
void update_len(ll a, ll b, ll add, ll node = 1, ll l = 1, ll r = n) {
    push_lazy(node, l, r);
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
        lazy[node] += add;
        push_lazy(node, l, r);
    } else {
        ll mid = (l + r) / 2;
        update_len(a, b, add, node * 2, l, mid);
        update_len(a, b, add, node * 2 + 1, mid + 1, r);
    }
}
ll min_speed(ll a, ll b, ll node = 1, ll l = 1, ll r = n) {
    push_lazy(node, l, r);
    if (l > b || r < a) return LLONG_MAX;
    if (l >= a && r <= b) return segtree[node].y;
    ll mid = (l + r) / 2;
    return min(min_speed(a, b, node * 2, l, mid), min_speed(a, b, node * 2 + 1, mid + 1, r));
}
ll to_root(ll pos, ll node = 1, ll l = 1, ll r = n) {
    push_lazy(node, l, r);
    if (l == r) return segtree[node].x;
    ll mid = (l + r) / 2;
    if (pos > mid) return to_root(pos, node * 2 + 1, mid + 1, r);
    return to_root(pos, node * 2, l, mid);
}

void dfs(ll node = 0, ll parent = -1) {
    bounds[node].x = ++t;
    for (ll i : graph[node]) {
        if (i != parent) dfs(i, node);
    }
    bounds[node].y = t;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    FOR(i, 1, n + 1) cin >> speed[i];
    FOR(i, 1, n + 1) {
        ll a, b, l;
        cin >> a >> b >> l;
        graph[a].push_back(b);
        graph[b].push_back(a);
        len[i] = {l, {a, b}};
    }
    dfs();
    assert(t == n);

    FOR(i, 1, n + 1) {
        update_speed(bounds[i].x, speed[i]);
        if (bounds[len[i].y.x].x < bounds[len[i].y.y].x) {
            update_len(bounds[len[i].y.y].x, bounds[len[i].y.y].y, len[i].x);
        } else {
            update_len(bounds[len[i].y.x].x, bounds[len[i].y.x].y, len[i].x);
        }
    }
    
    while (q--) {
        char c;
        cin >> c;
        if (c == 'Q') {
            ll i;
            cin >> i;
            cout << fixed << setprecision(6) << (double)to_root(bounds[i].x) / min_speed(bounds[i].x, bounds[i].y) << '\n';
        } else if (c == 'S') {
            ll i, k;
            cin >> i >> k;
            update_speed(bounds[i].x, k);
        } else {
            ll i, k;
            cin >> i >> k;
            if (bounds[len[i].y.x].x < bounds[len[i].y.y].x) {
                update_len(bounds[len[i].y.y].x, bounds[len[i].y.y].y, k - len[i].x);
            } else {
                update_len(bounds[len[i].y.x].x, bounds[len[i].y.x].y, k - len[i].x);
            }
            len[i].x = k;
        }
    }
    return 0;
}