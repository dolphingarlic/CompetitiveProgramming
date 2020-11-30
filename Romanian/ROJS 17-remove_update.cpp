/*
ROJS 2017 Remove Update
- Apply all updates using a lazy segtree, and then try undo each one
  and querying the range max
- Complexity: O(Q log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Query { int a, b, v; } queries[100001];

int n, q, segtree[400001], lazy[400001];

void push_lazy(int node, int l, int r) {
    segtree[node] += lazy[node];
    if (l != r) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
}

void update(int a, int b, int v, int node = 1, int l = 1, int r = n) {
    push_lazy(node, l, r);
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
        lazy[node] = v;
        push_lazy(node, l, r);
    } else {
        int mid = (l + r) / 2;
        update(a, b, v, node * 2, l, mid);
        update(a, b, v, node * 2 + 1, mid + 1, r);
        segtree[node] = max(segtree[node * 2], segtree[node * 2 + 1]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 0; i < q; i++) {
        cin >> queries[i].a >> queries[i].b >> queries[i].v;
        update(queries[i].a, queries[i].b, queries[i].v);
    }
    int ans = INT_MAX;
    for (int i = 0; i < q; i++) {
        update(queries[i].a, queries[i].b, -queries[i].v);
        ans = min(ans, segtree[1]);
        update(queries[i].a, queries[i].b, queries[i].v);
    }
    cout << ans;
    return 0;
}