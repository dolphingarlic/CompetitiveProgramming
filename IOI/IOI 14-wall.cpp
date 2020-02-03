#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Node {
    int lb, ub;
    Node operator+(Node b) { return {min(lb, b.lb), max(ub, b.ub)}; }
    Node operator-(Node b) { return {max(lb, b.lb), min(ub, b.ub)}; }
} segtree[8000001], lazy[8000001];
int n;

inline Node handle_cases(Node a, Node b) {
    if (a.lb >= b.ub)
        return {b.ub, b.ub};
    else if (a.ub <= b.lb)
        return {b.lb, b.lb};
    else
        return b - a;
}

inline void push_lazy(int node, int l, int r) {
    if (l != r) {
        lazy[node * 2] = handle_cases(lazy[node * 2], lazy[node]);
        lazy[node * 2 + 1] = handle_cases(lazy[node * 2 + 1], lazy[node]);
    } else segtree[node] = handle_cases(segtree[node], lazy[node]);
}

void update(int a, int b, int op, int h, int node = 1, int l = 1, int r = n) {
    if (lazy[node].lb != -1 || lazy[node].ub != INT_MAX) {
        push_lazy(node, l, r);
        lazy[node] = {-1, INT_MAX};
    }
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
        if (op == 1)
            lazy[node].lb = h;
        else
            lazy[node].ub = h;
    } else {
        int mid = (l + r) / 2;
        update(a, b, op, h, node * 2, l, mid);
        update(a, b, op, h, node * 2 + 1, mid + 1, r);
    }
}

int query(int a, int node = 1, int l = 1, int r = n) {
    if (lazy[node].lb != -1 || lazy[node].ub != INT_MAX) {
        push_lazy(node, l, r);
        lazy[node] = {-1, INT_MAX};
    }
    if (l == r) return segtree[node].lb;
    int mid = (l + r) / 2;
    if (a > mid)
        return query(a, node * 2 + 1, mid + 1, r);
    else
        return query(a, node * 2, l, mid);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k;
    cin >> n >> k;
    FOR(i, 1, 4 * n + 1) segtree[i] = {0, 0}, lazy[i] = {-1, INT_MAX};
    FOR(i, 0, k) {
        int op, a, b, h;
        cin >> op >> a >> b >> h;
        update(a + 1, b + 1, op, h);
    }
    FOR(i, 1, n + 1) cout << query(i) << '\n';
    return 0;
}