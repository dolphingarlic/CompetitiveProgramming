/*
SACO 2020 Tree Slugs
- Increment weights of edges on each path and check which one has weight > 0
- Just use DSU
- Complexity: O(N + K)
*/

#include <cstdio>
#include <vector>

int n, k;
std::vector<int> graph[100001];
int tin[100001], tout[100001], timer = 0;
int par[100001], cmp[100001];

void dfs(int node = 1, int parent = 0) {
    tin[node] = ++timer;
    cmp[node] = node;
    par[node] = parent;
    for (int i : graph[node]) if (i != parent) {
        dfs(i, node);
    }
    tout[node] = timer;
}

bool is_ancestor(int A, int B) {
    return tin[A] <= tin[B] && tout[A] >= tout[B];
}

int find(int A) {
    while (A != cmp[A]) A = cmp[A], cmp[A] = cmp[cmp[A]];
    return A;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs();
    int ans = 0;
    while (k--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a = find(a), b = find(b);
        while (!is_ancestor(a, b)) {
            ans++;
            a = cmp[a] = find(par[a]);
        }
        while (!is_ancestor(b, a)) {
            ans++;
            b = cmp[b] = find(par[b]);
        }
    }
    printf("%d", ans);
    return 0;
}