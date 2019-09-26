#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m;
int segtree[4004][4004], a[1001][1001];

int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }

void build_y(int x_node, int x_l, int x_r, int node = 1, int l = 1, int r = m) {
    if (l == r) {
        if (x_l == x_r) segtree[x_node][node] = a[x_l][l];
        else segtree[x_node][node] = gcd(segtree[x_node * 2][node], segtree[x_node * 2 + 1][node]);
    } else {
        int mid = (l + r) / 2;
        build_y(x_node, x_l, x_r, node * 2, l, mid);
        build_y(x_node, x_l, x_r, node * 2 + 1, mid + 1, r);
        segtree[x_node][node] = gcd(segtree[x_node][node * 2], segtree[x_node][node * 2 + 1]);
    }
}
void build_x(int node = 1, int l = 1, int r = n) {
    if (l != r) {
        int mid = (l + r) / 2;
        build_x(node * 2, l, mid);
        build_x(node * 2 + 1, mid + 1, r);
    }
    build_y(node, l, r);
}

void update_y(int x_node, int x_l, int x_r, int y, int val, int node = 1, int l = 1, int r = m) {
    if (l == r) {
        if (x_l == x_r) segtree[x_node][node] = val;
        else segtree[x_node][node] = gcd(segtree[x_node * 2][node], segtree[x_node * 2 + 1][node]);
    } else {
        int mid = (l + r) / 2;
        if (y <= mid) update_y(x_node, x_l, x_r, y, val, node * 2, l, mid);
        else update_y(x_node, x_l, x_r, y, val, node * 2 + 1, mid + 1, r);
        segtree[x_node][node] = gcd(segtree[x_node][node * 2], segtree[x_node][node * 2 + 1]);
    }
}
void update_x(int x, int y, int val, int node = 1, int l = 1, int r = n) {
    if (l != r) {
        int mid = (l + r) / 2;
        if (x <= mid) update_x(x, y, val, node * 2, l, mid);
        else update_x(x, y, val, node * 2 + 1, mid + 1, r);
    }
    update_y(node, l, r, y, val);
}

int query_y(int node_x, int y1, int y2, int node = 1, int l = 1, int r = m) {
    if (l > y2 || r < y1) return 0;
    if (l >= y1 && r <= y2) return segtree[node_x][node];
    int mid = (l + r) / 2;
    return gcd(query_y(node_x, y1, y2, node * 2, l, mid), query_y(node_x, y1, y2, node * 2 + 1, mid + 1, r));
}
int query_x(int x1, int x2, int y1, int y2, int node = 1, int l = 1, int r = n) {
    if (l > x2 || r < x1) return 0;
    if (l >= x1 && r <= x2) return query_y(node, y1, y2);
    int mid = (l + r) / 2;
    return gcd(query_x(x1, x2, y1, y2, node * 2, l, mid), query_x(x1, x2, y1, y2, node * 2 + 1, mid + 1, r));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) cin >> a[i][j];
    build_x();

    int q;
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        if (c == 'q') {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << query_x(x1, x2, y1, y2) << '\n';
        } else {
            int x, y, val;
            cin >> x >> y >> val;
            update_x(x, y, val);
        }
    }
    return 0;
}