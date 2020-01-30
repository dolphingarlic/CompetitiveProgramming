#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m;

vector<int> graph[100001];
int par[100001];

void dfs(int node = 1, int parent = 0) {
    par[node] = parent;
    for (int i : graph[node]) if (i != parent) dfs(i, node);
}

int find_root(int a) {
    while (par[a]) a = par[a];
    return a;
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
            if (a == par[b]) par[b] = 0;
            else par[a] = 0;
        } else {
            if (find_root(a) == find_root(b)) {
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