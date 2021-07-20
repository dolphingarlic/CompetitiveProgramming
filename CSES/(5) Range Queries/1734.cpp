#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, q, a[200001], bit[200001], res[200001];
tuple<int, int, int> queries[200001];
map<int, int> has;

void update(int pos, int val) {
    for (; pos <= n; pos += pos & -pos) bit[pos] += val;
}

int query(int l, int r) {
    int ans = 0;
    for (; r; r -= r & -r) ans += bit[r];
    for (l--; l; l -= l & -l) ans -= bit[l];
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        queries[i] = {r, l, i};
    }
    sort(queries + 1, queries + q + 1);
    int rptr = 1;
    for (int i = 1; i <= q; i++) {
        int r, l, idx;
        tie(r, l, idx) = queries[i];
        while (rptr <= r) {
            if (has.count(a[rptr])) update(has[a[rptr]], -1);
            update(rptr, 1);
            has[a[rptr]] = rptr;
            rptr++;
        }
        res[idx] = query(l, r);
    }
    for (int i = 1; i <= q; i++) cout << res[i] << '\n';
    return 0;
}