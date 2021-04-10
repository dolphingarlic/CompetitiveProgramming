/*
USACO 2021 UCFJ
- O(N^2) solution:
    - We try out each cow as the left endpoint of the subarray
    - Use a hashmap to keep track of the number of each breed of cow
      in the current subarray
    - The current subarray contributes (No. of distinct breeds - 2)
      to the answer if the two endpoints are also distinct
- To speed this up, we can use a lazy segment tree to activate/deactivate
  subarrays not containing distinct breeds and do range increment
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, b[200001], last_occ[200001], sec_last_occ[200001];
ll lazy[800001];
pair<int, ll> segtree[800001];

void push_lazy(int node, int l, int r) {
    segtree[node].second += lazy[node] * segtree[node].first;
    if (l != r) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
}

ll query(int x, int y, int node = 1, int l = 1, int r = n) {
    push_lazy(node, l, r);
    if (l > y || r < x) return 0;
    if (l >= x && r <= y) return segtree[node].second;
    int mid = (l + r) / 2;
    return query(x, y, node * 2, l, mid) + query(x, y, node * 2 + 1, mid + 1, r);
}

void rng_add(int x, int y, ll val, int node = 1, int l = 1, int r = n) {
    push_lazy(node, l, r);
    if (l > y || r < x) return;
    if (l >= x && r <= y) {
        lazy[node] = val;
        push_lazy(node, l, r);
    } else {
        int mid = (l + r) / 2;
        rng_add(x, y, val, node * 2, l, mid);
        rng_add(x, y, val, node * 2 + 1, mid + 1, r);
        segtree[node].second = segtree[node * 2].second + segtree[node * 2 + 1].second;
    }
}

void toggle(int pos, bool activate, int node = 1, int l = 1, int r = n) {
    push_lazy(node, l, r);
    if (l == r) segtree[node] = {activate, activate * segtree[node].second};
    else {
        int mid = (l + r) / 2;
        if (pos > mid) toggle(pos, activate, node * 2 + 1, mid + 1, r);
        else toggle(pos, activate, node * 2, l, mid);
        segtree[node] = {
            segtree[node * 2].first + segtree[node * 2 + 1].first,
            segtree[node * 2].second + segtree[node * 2 + 1].second
        };
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        ans += query(last_occ[b[i]] + 1, i);

        if (last_occ[b[i]]) {
            toggle(last_occ[b[i]], false);
            rng_add(sec_last_occ[b[i]] + 1, last_occ[b[i]] - 1, -1);
        }
        toggle(i, true);
        rng_add(last_occ[b[i]] + 1, i - 1, 1);

        sec_last_occ[b[i]] = last_occ[b[i]];
        last_occ[b[i]] = i;
    }
    cout << ans;
    return 0;
}
