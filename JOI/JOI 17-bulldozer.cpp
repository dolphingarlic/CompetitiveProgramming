/*
JOIOC 2017 Bulldozer
- Assume that the chosen lines have gradient m
    - Consider an arbitrary line perpendicular to the chosen lines (gradient = -1/m)
    - Project the points onto that line
    - Notice how we always take a contiguous subsegment of the projections
    - If we know m, then we can just use a segment tree to solve this
        - This works for subtask 1
- What happens when we rotate the chosen lines?
    - If we have 2 points A and B such that the gradient of AB is m, then
      when the gradient of the chosen lines goes from <m to >m, the projected
      positions of A and B swap
    - This means that for each pair of points, we can determine when they will be swapped
      just from the gradient of the line joining them
- If we sort the pairs of points by gradient, we can do an angle sweep to find the maximum over all
  gradients of the chosen lines
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Node {
    ll l, r, tot, best;

    Node operator+(Node B) {
        return {max(l, tot + B.l), max(B.r, r + B.tot), tot + B.tot, max(max(best, B.best), r + B.l)};
    }
} segtree[8001];

struct Point {
    ll x, y, v;

    bool operator<(Point B) {
        if (x == B.x) return y < B.y;
        return x < B.x;
    }
} points[2001];

struct Line {
    ll dx, dy;
    int u, v;

    bool operator<(Line B) {
        if (dy * B.dx == B.dy * dx) return tie(u, v) < tie(B.u, B.v);
        return dy * B.dx < B.dy * dx;
    }
} swaps[2000001];

int n, curr[2001];

void build(int node = 1, int l = 1, int r = n) {
    if (l == r) {
        ll v = max(points[l].v, 0ll);
        segtree[node] = {v, v, points[l].v, v};
    } else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }
}

void update(int pos, ll val, int node = 1, int l = 1, int r = n) {
    if (l == r) segtree[node] = {max(val, 0ll), max(val, 0ll), val, max(val, 0ll)};
    else {
        int mid = (l + r) / 2;
        if (pos > mid) update(pos, val, node * 2 + 1, mid + 1, r);
        else update(pos, val, node * 2, l, mid);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> points[i].x >> points[i].y >> points[i].v;
        curr[i] = i;
    }
    sort(points + 1, points + n + 1);
    int cnt = 0;
    FOR(i, 1, n + 1) FOR(j, i + 1, n + 1)
        swaps[cnt++] = {points[j].x - points[i].x, points[j].y - points[i].y, i, j};
    sort(swaps, swaps + cnt);

    build();
    ll ans = segtree[1].best;
    FOR(i, 0, cnt) {
        update(curr[swaps[i].u], points[swaps[i].v].v);
        update(curr[swaps[i].v], points[swaps[i].u].v);
        swap(curr[swaps[i].u], curr[swaps[i].v]);

        if (i == cnt - 1) ans = max(ans, segtree[1].best);
        else if (swaps[i].dy * swaps[i + 1].dx != swaps[i + 1].dy * swaps[i].dx) ans = max(ans, segtree[1].best);
    }
    cout << ans;
    return 0;
}