#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, q;
pair<int, int> a[200001];
int t[200001], segtree[2400001], bit[600001];
vector<pair<int, int>> c;
bool inv[200001], visited[200001];

void build(int node = 1, int l = 0, int r = 2 * n + q - 1) {
    if (l == r) segtree[node] = max(c[l].second, 0);
    else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
    }
}

int rmq(int x, int y, int node = 1, int l = 0, int r = 2 * n + q - 1) {
    if (l > y || r < x) return 0;
    if (l >= x && r <= y) return segtree[node];
    int mid = (l + r) / 2;
    return max(rmq(x, y, node * 2, l, mid), rmq(x, y, node * 2 + 1, mid + 1, r));
}

void add(int pos) { for (; pos <= q; pos += (pos & (-pos))) bit[pos]++; }

int rsq(int x, int y) {
    int ans = 0;
    for (; y; y -= (y & (-y))) ans += bit[y];
    for (x--; x; x -= (x & (-x))) ans -= bit[x];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    FOR(i, 1, n + 1) {
        cin >> a[i].first >> a[i].second;
        inv[i] = a[i].first < a[i].second;
        if (inv[i]) swap(a[i].first, a[i].second);
        
        c.push_back({a[i].first, -i});
        c.push_back({a[i].second, -i});
    }
    FOR(i, 1, q + 1) {
        cin >> t[i];
        c.push_back({t[i], i});
    }
    sort(c.begin(), c.end());
    build();

    FOR(i, 1, n + 1) {
        a[i].first = lower_bound(c.begin(), c.end(), make_pair(a[i].first, -i)) - c.begin();
        a[i].second = lower_bound(c.begin(), c.end(), make_pair(a[i].second, -i)) - c.begin();
    }

    ll ans = 0;
    for (int i = c.size() - 1; i; i--) {
        int k = c[i].second;
        if (k < 0) {
            k *= -1;
            if (visited[k]) continue;
            visited[k] = true;

            int mn = rmq(a[k].second, a[k].first);
            int cnt = rsq(mn + 1, q) + (mn == 0 && inv[k]);
            if (cnt & 1) ans += c[a[k].second].first;
            else ans += c[a[k].first].first;
        } else add(k);
    }
    cout << ans;
    return 0;
}