/*
Baltic 2014 Senior Postmen
- Notice that if we have the Eulerian cycle of the graph, we can kinda just
  split it up into the disjoint cycles required
    - It's given that the Eulerian cycle always exists
    - When we visit a node that's already part of the "visited cycle", print
      that cycle
    - Do this by storing the node visited next for each node
- Finding the Eulerian cycle is a standard problem
- Complexity: O(N + M)
*/

#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> graph[500001];
bool visited[500001], used[500001];
int nxt[500001];

void dfs(int node) {
    if (visited[node]) {
        while (visited[node]) {
            visited[node] = false;
            cout << node << ' ';
            node = nxt[node];
        }
        cout << '\n';
    }
    while (graph[node].size()) {
        int c, idx;
        tie(c, idx) = graph[node].back();
        graph[node].pop_back();
        if (!used[idx]) {
            used[idx] = true;
            visited[node] = true;
            nxt[node] = c;
            dfs(c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back({b, i});
        graph[b].push_back({a, i});
    }
    
    dfs(1);
    return 0;
}
