#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
using namespace __gnu_pbds;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;

indexed_set segtree[400000];
int N, Q, cnt = 1;
pair<int, int> A[100000];

void build(int node = 1, int l = 0, int r = N - 1) {
    if (l == r) segtree[node].insert(A[l]);
    else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        for (auto& i : segtree[node * 2]) segtree[node].insert(i);
        for (auto& i : segtree[node * 2 + 1]) segtree[node].insert(i);
    }
}
ll query(int a, int b, pair<int, int> val, int node = 1, int l = 0, int r = N - 1) {
    if (a > b || a > r || b < l) return 0;
    if (a <= l && b >= r) return segtree[node].order_of_key(val);

    int mid = (l + r) / 2;
    return query(a, b, val, node * 2, l, mid) + query(a, b, val, node * 2 + 1, mid + 1, r);
}
void update(int pos, pair<int, int> old, pair<int, int> val, int node = 1, int l = 0, int r = N - 1) {
    segtree[node].erase(old);
    segtree[node].insert(val);
    if (l != r) {
        int mid = (l + r) / 2;
        if (pos > mid) update(pos, old, val, node * 2 + 1, mid + 1, r);
        else update(pos, old, val, node * 2, l, mid);
    }
}

int main() {
    scanf("%d %d", &N, &Q);
    FOR(i, 0, N) {
        int X;
        scanf("%d", &X);
        A[i] = {X, cnt++};
    }

    build();    
    ll curr = 0;
    FOR(i, 0, N) curr += query(i, N - 1, {A[i].first, -1});

    printf("%lld\n", curr);

    while (Q--) {
        int X, Y;
        scanf("%d %d", &X, &Y);

        curr -= query(X + 1, N - 1, {A[X].first, -1}) - query(0, X - 1, {A[X].first, INT_MAX});
        update(X, A[X], {Y, cnt});
        A[X] = {Y, cnt++};
        curr += query(X + 1, N - 1, {A[X].first, -1}) - query(0, X - 1, {A[X].first, INT_MAX});

        printf("%lld\n", curr);
    }
}
