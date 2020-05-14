/*
POI 2006 Tetris3D
- Firstly, realize that we can't do lazy propagation on a 2D segtree and cry a bit
- Next, notice that heights only ever increase
- This is similar to the 1D version of range updates/queries where we can't
  use lazy propagation
    - Basically, for each node, we store 2 values:
        - The maximum of that range (max[i])
        - The maximum of the last time every value in that range was equal (all[i])
    - Since the values only ever increase, we know that if we have a segment (l, r)
      and the query range intersects it, the answer to the query is always >= all[i]
- We can apply this idea to our 2D segtree, but the inner 1D segtrees do support lazy
  propagation
    - Each node of the 2D segtree stores 2 1D segtrees: range_max and range_all
- Complexity: O(N log S log D)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Segtree {
    int seg_val[2048], lazy[2048];

    void push_lazy(int node, int l, int r) {
        seg_val[node] = max(seg_val[node], lazy[node]);
        if (l != r) {
            lazy[node * 2] = max(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = max(lazy[node * 2 + 1], lazy[node]);
        }
        lazy[node] = 0;
    }

    void update(int yl, int yr, int val, int node = 1, int l = 0, int r = 999) {
        push_lazy(node, l, r);
        if (l > yr || r < yl) return;
        if (l >= yl && r <= yr) {
            lazy[node] = val;
            push_lazy(node, l, r);
        } else {
            int mid = (l + r) / 2;
            update(yl, yr, val, node * 2, l, mid);
            update(yl, yr, val, node * 2 + 1, mid + 1, r);
            seg_val[node] = max(seg_val[node * 2], seg_val[node * 2 + 1]);
        }
    }

    int query(int yl, int yr, int node = 1, int l = 0, int r = 999) {
        push_lazy(node, l, r);
        if (l > yr || r < yl) return 0;
        if (l >= yl && r <= yr) return seg_val[node];
        int mid = (l + r) / 2;
        return max(query(yl, yr, node * 2, l, mid),
                   query(yl, yr, node * 2 + 1, mid + 1, r));
    }
};

struct Lazy2dSegtree {
    Segtree range_all[2048], range_max[2048];

    void update(int xl, int xr, int yl, int yr, int val, int node = 1, int l = 0, int r = 999) {
        if (l > xr || r < xl) return;
        if (l >= xl && r <= xr) {
            range_all[node].update(yl, yr, val);
            range_max[node].update(yl, yr, val);
        } else {
            int mid = (l + r) / 2;
            update(xl, xr, yl, yr, val, node * 2, l, mid);
            update(xl, xr, yl, yr, val, node * 2 + 1, mid + 1, r);
            range_max[node].update(yl, yr, val);
        }
    }

    int query(int xl, int xr, int yl, int yr, int node = 1, int l = 0, int r = 999) {
        if (l > xr || r < xl) return 0;
        if (l >= xl && r <= xr) return range_max[node].query(yl, yr);
        int mid = (l + r) / 2;
        return max(max(query(xl, xr, yl, yr, node * 2, l, mid),
                       query(xl, xr, yl, yr, node * 2 + 1, mid + 1, r)),
                   range_all[node].query(yl, yr));
    }
} board;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int D, S, N;
    cin >> D >> S >> N;

    while (N--) {
        int d, s, w, x, y;
        cin >> d >> s >> w >> x >> y;
        int mx = board.query(x, x + d - 1, y, y + s - 1);
        board.update(x, x + d - 1, y, y + s - 1, mx + w);
    }
    cout << board.query(0, D - 1, 0, S - 1);
    return 0;
}