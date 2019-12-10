#include "holiday.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll ans = 0;
int n, s, d, loc[100001], ptr;
pair<int, int> a[100001];

pair<ll, int> segtree[400001];
void add_city(int pos, bool inserting, int node = 1, int l = 1, int r = n) {
    if (l == r) {
        if (inserting) segtree[node] = {a[pos].first, 1};
        else segtree[node] = {0, 0};
    } else {
        int mid = (l + r) / 2;
        if (pos > mid) add_city(pos, inserting, node * 2 + 1, mid + 1, r);
        else add_city(pos, inserting, node * 2, l, mid);
        segtree[node] = {segtree[node * 2].first + segtree[node * 2 + 1].first,
                         segtree[node * 2].second + segtree[node * 2 + 1].second};
    }
}
ll k_best(int k, int node = 1, int l = 1, int r = n) {
    if (k <= 0) return 0;
    if (segtree[node].second <= k) return segtree[node].first;
    int mid = (l + r) / 2;
    if (segtree[node * 2].second >= k) return k_best(k, node * 2, l, mid);
    return segtree[node * 2].first + k_best(k - segtree[node * 2].second, node * 2 + 1, mid + 1, r);
}

void solve(int l, int r, int lopt, int ropt) {
    if (l > r) return;

    int mid = (l + r) / 2;
    pair<ll, int> best = {LLONG_MIN, -1};

    // Update range
    if (mid < ptr) FOR(i, mid, ptr) add_city(loc[i], true);
    else FOR(i, ptr, mid) add_city(loc[i], false);
    ptr = mid;

    // D&C to find opt
    FOR(i, lopt, ropt + 1) {
        add_city(loc[i], true);
        best = max(best, {k_best(d + 2 * mid - s - i), -i});
    }

    ans = max(ans, best.first);
    int opt = -best.second;

    // Recursively solve left and right
    FOR(i, opt, ropt + 1) add_city(loc[i], false);
    solve(mid + 1, r, opt, ropt);
    FOR(i, lopt, opt) add_city(loc[i], false);
    solve(l, mid - 1, lopt, opt);
}

ll findMaxAttraction(int N, int S, int D, int A[]) {
    n = N, s = S + 1, d = D;
    FOR(i, 1, n + 1) a[i] = {A[i - 1], i};
    sort(a + 1, a + n + 1, greater<pair<int, int>>());
    FOR(i, 1, n + 1) loc[a[i].second] = i;

    ptr = s + 1;
    solve(1, s, s, n);

    // Reverse the whole thing
    FOR(i, 1, n + 1) {
        loc[n - a[i].second + 1] = i;
        add_city(i, false);
    }
    s = n - s + 1;

    ptr = s + 1;
    solve(1, s, s, n);

    return ans;
}
