#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MAXN 1000001
using namespace std;

int n, m, c;
int a[MAXN];
pair<int, int> segtree[4 * MAXN];

pair<int, int> query(int a, int b, int node = 1, int l = 1, int r = n) {
    if (b < l || a > r) return {INT_MIN, INT_MAX};
    if (l >= a && r <= b) return segtree[node];
    int mid = (l + r) / 2;
    pair<int, int> x = query(a, b, node * 2, l, mid), y = query(a, b, node * 2 + 1, mid + 1, r);
    return {max(x.first, y.first), min(x.second, y.second)};
}

void build(int node = 1, int l = 1, int r = n) {
    if (l == r) segtree[node] = {a[l], a[l]};
    else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        segtree[node] = {
            max(segtree[node * 2].first, segtree[node * 2 + 1].first),
            min(segtree[node * 2].second, segtree[node * 2 + 1].second)};
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> c;
    FOR(i, 1, n + 1) cin >> a[i];
    build();
    
    vector<int> s;
    FOR(i, 1, n - m + 2) {
        pair<int, int> q = query(i, i + m - 1);
        if (q.first - q.second <= c) s.push_back(i);
    }
    if (s.size()) for (int i : s) cout << i << '\n';
    else cout << "NONE";
    return 0;
}