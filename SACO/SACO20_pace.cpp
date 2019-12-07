#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Node {
    Node *l, *r;
    int sum;

    Node(int val) {
        l = nullptr, r = nullptr;
        sum = val;
    }

    Node(Node *ll, Node *rr) {
        l = ll, r = rr;
        sum = 0;
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

int n, m, k, best[2049];
Node* persist_roots[1025];

Node* build(int l = 1, int r = n) {
    if (l == r) return new Node(10000);
    int mid = (l + r) / 2;
    return new Node(build(l, mid), build(mid + 1, r));
}

int query(Node* node, int a, int b, int l = 1, int r = n) {
    if (l > b || r < a) return 0;
    if (l >= a && r <= b) return node->sum;
    int mid = (l + r) / 2;
    return query(node->l, a, b, l, mid) + query(node->r, a, b, mid + 1, r);
}

Node* update(Node* node, int pos, int val, int l = 1, int r = n) {
    if (l == r) return new Node(val);
    int mid = (l + r) / 2;
    if (pos > mid) return new Node(node->l, update(node->r, pos, val, mid + 1, r));
    else return new Node(update(node->l, pos, val, l, mid), node->r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k;
    fill(best + 1, best + n + 1, 10000);
    persist_roots[0] = build();
    FOR(i, 1, m + 1) {
        persist_roots[i] = persist_roots[i - 1];
        FOR(j, 1, n + 1) {
            int x;
            cin >> x;
            if (x < best[j]) {
                persist_roots[i] = update(persist_roots[i], j, x);
                best[j] = x;
            }
        }
    }

    while (k--) {
        int l, r, t;
        cin >> l >> r >> t;
        cout << query(persist_roots[t], l, r) << '\n';
    }
    return 0;
}