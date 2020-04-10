/*
IOI 2008 Pyramid Base
- Case B = 0:
    - Let r[l] be the right x-coordinate if the left x-coordinate of the pyramid base is l
    - Notice how r[l] >= r[l - 1]
    - This means we can use 2 pointers to find the largest r - l
    - To find the maximum height of a pyramid with x-coordinates in the range [l, r], we can use
      a segment tree that supports range increment and stores the maximum number of consecutive 0s
        - We don't actually need lazy propagation because we only care about the number of consecutive 0s
    - See SACO 2018 Stadium for a similar problem
    - Complexity: O((N + P) log N)
- Case B > 0:
    - Binary search for the side length L
    - Cosider an array C where C[i] is the cost to build a pyramid with bottom y-coordinate at i
    - When we add an obstacle, we increase all values C[y1] to C[y2 + L - 1] by its cost
    - We can now just use a lazy segment tree to keep track of the minimum value of all values C[L] to C[W]
    - Complexity: O((N + P) log^2 N)
*/

#include <bits/stdc++.h>
#pragma GCC target("sse4,avx2,fma,avx")
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

namespace no_remove {
    struct Node {
        int sm, range, mxl, mxr, mxt;
    };

    Node segtree[3000001];
    vector<pair<int, int>> add[1000002], subtr[1000002];

    void combine(int node, Node l, Node r) {
        if (l.sm) l.mxl = l.mxr = l.mxt = 0;
        if (r.sm) r.mxl = r.mxr = r.mxt = 0;
        segtree[node] = {segtree[node].sm, l.range + r.range,
                         l.mxl + (l.mxl == l.range ? r.mxl : 0),
                         r.mxr + (r.mxl == r.range ? l.mxr : 0),
                         max({l.mxt, r.mxt, l.mxr + r.mxl})};
    }

    void build(int node, int l, int r) {
        if (l == r) segtree[node] = {0, 1, 1, 1, 1};
        else {
            int mid = (l + r) / 2;
            build(node * 2, l, mid);
            build(node * 2 + 1, mid + 1, r);
            combine(node, segtree[node * 2], segtree[node * 2 + 1]);
        }
    }

    void update(int a, int b, int val, int node, int l, int r) {
        if (l > b || r < a) return;
        if (l >= a && r <= b) segtree[node].sm += val;
        else {
            int mid = (l + r) / 2;
            update(a, b, val, node * 2, l, mid);
            update(a, b, val, node * 2 + 1, mid + 1, r);
            combine(node, segtree[node * 2], segtree[node * 2 + 1]);
        }
    }

    void solve(int H, int W) {
        add[H + 1].push_back({1, W});
        int N, C;
        cin >> N;
        FOR(i, 0, N) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2 >> C;
            add[x1].push_back({y1, y2});
            subtr[x2 + 1].push_back({y1, y2});
        }
        build(1, 1, W);

        int ans = 0, rptr = 1;
        FOR(lptr, 1, H + 1) {
            for (pair<int, int> i : subtr[lptr]) update(i.first, i.second, -1, 1, 1, W);
            while ((segtree[1].sm ? 0 : segtree[1].mxt) >= rptr - lptr) {
                for (pair<int, int> i : add[rptr]) update(i.first, i.second, 1, 1, 1, W);
                ans = max(ans, rptr++ - lptr);
            }
        }
        cout << ans;
    }
}

namespace yes_remove {
    int lazy[3000001], segtree[3000001];
    vector<array<int, 3>> add[1000002], subtr[1000002];
    
    inline void push_lazy(int node, int l, int r) {
        segtree[node] += lazy[node];
        if (l != r) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    void update(int a, int b, int val, int node, int l, int r) {
        push_lazy(node, l, r);
        if (l > b || r < a) return;
        if (l >= a && r <= b) {
            lazy[node] = val;
            push_lazy(node, l, r);
        } else {
            int mid = (l + r) / 2;
            update(a, b, val, node * 2, l, mid);
            update(a, b, val, node * 2 + 1, mid + 1, r);
            segtree[node] = min(segtree[node * 2], segtree[node * 2 + 1]);
        }
    }

    bool check(int len, int H, int W, int B) {
        memset(segtree, 0, sizeof(segtree));
        memset(lazy, 0, sizeof(lazy));
        update(1, len - 1, B + 1, 1, 1, W);
        FOR(i, 1, len) for (auto j : add[i]) update(j[0], j[1] + len - 1, j[2], 1, 1, W);
        FOR(i, len, H + 1) {
            for (auto j : add[i]) update(j[0], j[1] + len - 1, j[2], 1, 1, W);
            for (auto j : subtr[i - len + 1]) update(j[0], j[1] + len - 1, -j[2], 1, 1, W);
            if (segtree[1] <= B) return true;
        }
        return false;
    }

    void solve(int H, int W, int B) {
        int N;
        cin >> N;
        FOR(i, 0, N) {
            int x1, y1, x2, y2, c;
            cin >> x1 >> y1 >> x2 >> y2 >> c;
            add[x1].push_back({y1, y2, c});
            subtr[x2 + 1].push_back({y1, y2, c});
        }

        int l = 1, r = min(H, W);
        while (l != r) {
            int mid = (l + r + 1) / 2;
            if (check(mid, H, W, B)) l = mid;
            else r = mid - 1;
        }
        cout << l;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int H, W, B;
    cin >> H >> W >> B;
    if (B) yes_remove::solve(H, W, B);
    else no_remove::solve(H, W);
    return 0;
}
