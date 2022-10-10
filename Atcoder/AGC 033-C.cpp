#include <iostream>
#include <utility>
#include <vector>
using namespace std;

vector<int> graph[200001];

pair<int, int> dfs(int node = 1, int parent = 0) {
    pair<int, int> ret = {node, 1};
    for (int i : graph[node])
        if (i != parent) {
            pair<int, int> cand = dfs(i, node);
            if (cand.second >= ret.second) ret = {cand.first, cand.second + 1};
        }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    if (dfs(dfs().first).second % 3 == 2)
        cout << "Second";
    else
        cout << "First";
    return 0;
}
