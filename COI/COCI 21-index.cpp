/*
COCI 2021 Index
- Let paper i be a point (i, p[i]) in the Cartesian plane
- A query is basically finding the largest M such that the number of points
  in the rectangle (l[j], 2e5)->(r[j], M) is at least M
- We can binary search for M and use a persistent segment tree to do static
  2D range sum queries
- Complexity: O(N log^2 N)
*/

#include <bits/stdc++.h>
using namespace std;

const int MX = 2e5 + 1;

struct Node {
    int l, r, cnt;
    Node *lc, *rc;

    Node(int x, int c = 0): l(x), r(x), cnt(c), lc(nullptr), rc(nullptr) {}
    Node(Node *llc, Node *rrc) {
        lc = llc, rc = rrc;
        l = lc->l, r = rc->r;
        cnt = lc->cnt + rc->cnt;
    }
};

Node *build(int l = 1, int r = MX) {
    if (l == r) return new Node(l);
    int mid = (l + r) >> 1;
    return new Node(build(l, mid), build(mid + 1, r));
}

Node *increment(Node *node, int pos, int l = 1, int r = MX) {
    if (l == r) return new Node(l, node->cnt + 1);
    int mid = (l + r) >> 1;
    if (pos > mid) return new Node(node->lc, increment(node->rc, pos, mid + 1, r));
    return new Node(increment(node->lc, pos, l, mid), node->rc);
}

int query(Node *node, int pos, int l = 1, int r = MX) {
    if (r < pos) return 0;
    if (l >= pos) return node->cnt;
    int mid = (l + r) >> 1;
    return query(node->lc, pos, l, mid) + query(node->rc, pos, mid + 1, r);
}

int n, q, p[MX];
Node *persist_roots[MX];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> p[i];
    persist_roots[0] = build();
    for (int i = 1; i <= n; i++) persist_roots[i] = increment(persist_roots[i - 1], p[i]);

    while (q--) {
        int x, y;
        cin >> x >> y;
        int l = 1, r = y - x + 1;
        while (l != r) {
            int mid = (l + r + 1) >> 1;
            if (query(persist_roots[y], mid) - query(persist_roots[x - 1], mid) >= mid)
                l = mid;
            else
                r = mid - 1;
        }
        cout << l << '\n';
    }
    return 0;
}