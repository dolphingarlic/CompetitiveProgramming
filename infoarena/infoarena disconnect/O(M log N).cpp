#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int n, m;
 
// DFS
vector<int> graph[100001];
int timer = 1, tin[100001], tout[100001];
int anc[100001][18];
 
void dfs(int node = 1, int parent = 0) {
    anc[node][0] = parent;
    for (int i = 1; i < 18 && anc[node][i - 1]; i++)
        anc[node][i] = anc[anc[node][i - 1]][i - 1];
 
    tin[node] = timer++;
    for (int i : graph[node]) if (i != parent) dfs(i, node);
    tout[node] = timer;
}
 
// Fenwick tree
int bit[100001];

void update(int pos, int val) { for (; pos <= n; pos += (pos & (-pos))) bit[pos] += val; }

int query(int pos) {
    int ans = 0;
    for (; pos; pos -= (pos & (-pos))) ans += bit[pos];
    return ans;
}
 
// Binary lifting
int find_ancestor(int node) {
    int lca = node;
    for (int i = 17; ~i; i--) {
        if (anc[lca][i] && query(tin[anc[lca][i]]) == query(tin[node])) lca = anc[lca][i];
    }
    return lca;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("disconnect.in", "r", stdin);
    freopen("disconnect.out", "w", stdout);
    cin >> n >> m;
    FOR(i, 1, n) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs();
 
    int v = 0;
    while (m--) {
        int t, x, y;
        cin >> t >> x >> y;
        int a = x ^ v, b = y ^ v;
 
        if (t == 1) {
            if (anc[b][0] == a) swap(a, b);
            update(tin[a], 1);
            update(tout[a], -1);
        } else {
            if (find_ancestor(a) == find_ancestor(b)) {
                cout << "YES\n";
                v = a;
            } else {
                cout << "NO\n";
                v = b;
            }
        }
    }
    return 0;
}
