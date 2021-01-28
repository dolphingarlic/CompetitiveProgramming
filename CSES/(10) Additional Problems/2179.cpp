#include <bits/stdc++.h>
using namespace std;

vector<int> graph[100001];
int visited[100001], odd[100001], timer = 1;
vector<pair<int, int>> ans;

void dfs(int node, int parent = 0) {
    visited[node] = timer++;
    for (int i : graph[node]) if (i != parent) {
        if (!visited[i]) {
            dfs(i, node);
            if (odd[i]) {
                ans.push_back({i, node});
                odd[i] = 0;
            } else {
                ans.push_back({node, i});
                odd[node] ^= 1;
            }
        } else if (visited[node] > visited[i]) {
            ans.push_back({node, i});
            odd[node] ^= 1;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    scanf("%d %d", &n, &m);
    while (m--) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) if (!visited[i]) dfs(i);
    if (accumulate(odd + 1, odd + n + 1, 0)) printf("IMPOSSIBLE");
    else for (pair<int, int> i : ans) printf("%d %d\n", i.first, i.second);
    return 0;
}
