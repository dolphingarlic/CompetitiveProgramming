/*
NOI.cn 2010 Super Piano
- First, build a prefix sum array of the note values
- The best chord we can make starting on note i has value
    max(pref[j] : j from i + l to i + r) - pref[i - 1]
- This is a range query, so we can use a segment tree to
  handle it and remove that optimal position after using it
- However, there can be multiple different starting notes,
  so we can't just straight-up remove values from the segtree,
  since other starting positions could potentially depend on
  those
- To address this, simply use a persistent segtree so that
  each starting position has its own segtree
- There are O(K + N) nodes because we update K times
- Complexity: O((K + N) log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Node {
    pair<int, int> val;
    Node *lc, *rc;

    Node(pair<int, int> _val) : val(_val), lc(nullptr), rc(nullptr) {}

    Node(Node *_lc, Node *_rc) : lc(_lc), rc(_rc), val({INT_MIN, -1}) {
        if (lc) val = max(val, lc->val);
        if (rc) val = max(val, rc->val);
    }
} * persist_roots[500001];

int n, x, y, k, pref[500001];

Node *build(int l = 1, int r = n) {
    if (l == r) return new Node({pref[l], l});
    int mid = (l + r) / 2;
    return new Node(build(l, mid), build(mid + 1, r));
}

pair<int, int> query(Node *node, int a, int b, int l = 1, int r = n) {
    if (!node || r < a || l > b) return {INT_MIN, -1};
    if (l >= a && r <= b) return node->val;
    int mid = (l + r) / 2;
    return max(query(node->lc, a, b, l, mid),
               query(node->rc, a, b, mid + 1, r));
}

Node *update(Node *node, int pos, int l = 1, int r = n) {
    if (l == r) return nullptr;
    int mid = (l + r) / 2;
    if (pos > mid) return new Node(node->lc, update(node->rc, pos, mid + 1, r));
    return new Node(update(node->lc, pos, l, mid), node->rc);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k >> x >> y;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        pref[i] = pref[i - 1] + a;
    }
    Node *init_root = build();
    for (int i = 1; i <= n - x + 1; i++) persist_roots[i] = init_root;

    priority_queue<pair<int, int>> pq;
    for (int i = 1; i <= n - x + 1; i++) {
        pair<int, int> res = query(persist_roots[i], i + x - 1, i + y - 1);
        pq.push({res.first - pref[i - 1], i});
        persist_roots[i] = update(persist_roots[i], res.second);
    }
    ll ans = 0;
    while (k--) {
        int v, i;
        tie(v, i) = pq.top();
        pq.pop();
        ans += v;
        pair<int, int> res = query(persist_roots[i], i + x - 1, i + y - 1);
        pq.push({res.first - pref[i - 1], i});
        persist_roots[i] = update(persist_roots[i], res.second);
    }
    cout << ans;
    return 0;
}
