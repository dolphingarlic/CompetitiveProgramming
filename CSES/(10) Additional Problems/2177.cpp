#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<pair<int, int>> ans, graph[100001];
bool visited[100001], in_ans[200001];
int tin[100001], low[100001], timer = 0;

void dfs(int node = 1, int parent = 0) {
    visited[node] = true;
    tin[node] = low[node] = timer++;
    for (pair<int, int> i : graph[node]) if (i.first != parent) {
        if (!in_ans[i.second]) {
            ans.push_back({node, i.first});
            in_ans[i.second] = true;
        }
        if (visited[i.first]) low[node] = min(low[node], tin[i.first]);
        else {
            dfs(i.first, node);
            low[node] = min(low[node], low[i.first]);
            if (low[i.first] > tin[node]) {
                cout << "IMPOSSIBLE";
                exit(0);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, m});
        graph[v].push_back({u, m});
    }
    dfs();
    if (find(visited + 1, visited + n + 1, false) != visited + n + 1)
        return cout << "IMPOSSIBLE", 0;
    for (pair<int, int> i : ans) cout << i.first << ' ' << i.second << '\n';
    return 0;
}