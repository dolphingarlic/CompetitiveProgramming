/*
IZhO 2014 Divide
- For any left mine, it's always optimal to pick the rightmost
  valid right mine
    - This is because all g[i] are positive
- Let pref_d[i] = sum(d[j] for j <= i) - x[i]
- Notice how if pref_d[i] <= pref_d[j] and i <= j, then we can use
  all mines in the range [i, j]
- Using a segment tree, we can find the rightmost such j for each i
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, x[100001], g[100001], d[100001];
ll pref_g[100001], pref_d[100001];

ll segtree[400001];

void build(int node = 1, int l = 1, int r = n) {
    if (l == r) segtree[node] = pref_d[l];
    else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
    }
}

int query(int pos, int node = 1, int l = 1, int r = n) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (pos > mid || segtree[node * 2 + 1] >= pref_d[pos] - d[pos])
        return query(pos, node * 2 + 1, mid + 1, r);
    return query(pos, node * 2, l, mid);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> x[i] >> g[i] >> d[i];
        pref_g[i] = pref_g[i - 1] + g[i];
        pref_d[i] = pref_d[i - 1] + d[i] - x[i] + x[i - 1];
    }
    build();

    ll ans = 0;
    FOR(i, 1, n + 1) {
        int opt = query(i);
        ans = max(ans, pref_g[opt] - pref_g[i - 1]);
    }
    cout << ans;
    return 0;
}