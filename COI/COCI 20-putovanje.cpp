/*
COCI 2020 Putovanje
- Essentially want to find the number of times we traverse each edge
- We use the fact that A->B = A->LCA(A, B)->B
    - A path A->B where B is an ancestor of A passes through the "parent"
      edge of C iff B is an ancestor of C and C is an ancestor of A
    - This means we can mark A with 1 and B with -1
    - So the subtree sum is the number of paths passing through an edge!
- DFS to get DFS order and use a Fenwick tree to do stuff
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n;
vector<int> graph[200001];
ll bit[200001];
int tin[200001], tout[200001], timer = 0;
int anc[200001][20];

void dfs(int node = 1, int parent = 0) {
    anc[node][0] = parent;
    FOR(i, 1, 20) anc[node][i] = anc[anc[node][i - 1]][i - 1];

    tin[node] = ++timer;
    for (int i : graph[node]) if (i != parent) dfs(i, node);
    tout[node] = timer;
}

bool is_ancestor(int a, int b) { return tin[a] <= tin[b] && tout[a] >= tout[b]; }

int lca(int a, int b) {
    if (is_ancestor(a, b)) return a;
    for (int i = 19; ~i; i--) {
        if (anc[a][i] && !is_ancestor(anc[a][i], b)) a = anc[a][i];
    }
    return anc[a][0];
}

void update(int pos, ll val) { for (; pos <= n; pos += (pos & (-pos))) bit[pos] += val; }

ll query(int a, int b) {
    ll ans = 0;
    for (; b; b -= (b & (-b))) ans += bit[b];
    for (a--; a; a -= (a & -a)) ans -= bit[a];
    return ans;
}

vector<int> edges[200001];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    FOR(i, 1, n) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        graph[a].push_back(b);
        graph[b].push_back(a);
        edges[i] = {a, b, c, d};
    }
    dfs();

    FOR(i, 1, n) {
        int l = lca(i, i + 1);
        update(tin[i], 1);
        update(tin[i + 1], 1);
        update(tin[l], -2);
    }

    ll ans = 0;
    FOR(i, 1, n) {
        int x;
        if (is_ancestor(edges[i][0], edges[i][1])) x = edges[i][1];
        else x = edges[i][0];

        ans += min((ll)edges[i][3], (ll)edges[i][2] * query(tin[x], tout[x]));
    }
    cout << ans;
    return 0;
}