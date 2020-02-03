#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, timer = 1, tin[100001], tout[100001];
vector<int> graph[100001];

void dfs(int node = 1, int parent = -1) {
    tin[node] = timer++;
    for (int i : graph[node]) {
        if (i != parent) dfs(i, node);
    }
    tout[node] = timer - 1;
}

set<pair<int, int>> up[100001];

ll lazy[400001], segtree[400001];
void push_lazy(int node, int l, int r) {
    segtree[node] += lazy[node] * (r - l + 1);
    if (l != r) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
}
void update(int a, int b, ll val, int node = 1, int l = 1, int r = n) {
    push_lazy(node, l, r);
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
        lazy[node] = val;
        push_lazy(node, l, r);
    } else {
        int mid = (l + r) / 2;
        update(a, b, val, node * 2, l, mid);
        update(a, b, val, node * 2 + 1, mid + 1, r);
        segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
    }
}
ll query(int a, int b, int node = 1, int l = 1, int r = n) {
    push_lazy(node, l, r);
    if (l > b || r < a) return 0;
    if (l >= a && r <= b) return segtree[node];
    int mid = (l + r) / 2;
    return query(a, b, node * 2, l, mid) + query(a, b, node * 2 + 1, mid + 1, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);
    int q;
    cin >> n >> q;
    FOR(i, 1, n) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs();

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, c;
            cin >> v >> c;

            bool process = true;
            if (up[c].size()) {
                auto par = up[c].upper_bound({tin[v], tout[v]});
                if (par != up[c].begin() && (*prev(par)).second >= tout[v]) process = false;
            }
            if (process) {
                auto lchi = up[c].upper_bound({tin[v], tout[v]});
                auto rchi = lchi;
                for (; rchi != up[c].end() && (*rchi).second <= tout[v]; rchi++) {
                    update((*rchi).first, (*rchi).second, -1);
                }
                up[c].erase(lchi, rchi);

                update(tin[v], tout[v], 1);
                up[c].insert({tin[v], tout[v]});
            }
        } else {
            int v;
            cin >> v;
            cout << query(tin[v], tout[v]) << '\n';
        }
    }
    return 0;
}