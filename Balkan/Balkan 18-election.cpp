#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Node {
    int l_min, r_min, tot, ans;

    Node operator+(Node b) {
        Node ret;
        ret.l_min = max(l_min, b.l_min - tot);
        ret.r_min = max(r_min - b.tot, b.r_min);
        ret.tot = tot + b.tot;
        ret.ans = max(max(ans - b.tot, b.ans - tot), l_min + b.r_min);
        return ret;
    }
};

Node segtree[2000001];
char s[500001];
int n;

void build(int node = 1, int l = 1, int r = n) {
    if (l == r) {
        if (s[l] == 'T') segtree[node] = {1, 1, -1, 1};
        else segtree[node] = {0, 0, 1, 0};
    } else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }
}

Node query(int a, int b, int node = 1, int l = 1, int r = n) {
    if (l > b || r < a) return {0, 0, 0, 0};
    if (l >= a && r <= b) return segtree[node];
    int mid = (l + r) / 2;
    return query(a, b, node * 2, l, mid) + query(a, b, node * 2 + 1, mid + 1, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    FOR(i, 1, n + 1) cin >> s[i];
    build();
    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << query(a, b).ans << '\n';
    }
    return 0;
}