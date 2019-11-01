#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

vector<int> graph[50001], reversed[50001], stck;
bool visited[50001];
int sz[50001], cmp[50001], scc = 1;
set<int> conn[50001];

void dfs1(int node) {
    visited[node] = true;
    for (int i : graph[node])
        if (!visited[i]) dfs1(i);
    stck.push_back(node);
}

void dfs2(int node) {
    cmp[node] = scc;
    sz[scc]++;
    for (int i : reversed[node]) {
        if (!cmp[i])
            dfs2(i);
        else if (cmp[i] != scc)
            conn[scc].insert(cmp[i]);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    FOR(i, 0, m) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    FOR(i, 1, n + 1) if (!visited[i]) dfs1(i);
    FOR(i, 1, n + 1) for (int j : graph[i]) reversed[j].push_back(i);
    while (stck.size()) {
        if (!cmp[stck.back()]) {
            dfs2(stck.back());
            scc++;
        }
        stck.pop_back();
    }

    for (int i = scc - 1; i; i--) {
        for (int j : conn[i]) sz[j] += sz[i];
    }

    FOR(i, 1, n + 1) cout << sz[cmp[i]] - 1 << '\n';
}
