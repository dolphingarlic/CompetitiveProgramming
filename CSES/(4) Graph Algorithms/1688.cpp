#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[100001];
int side[100001];

void dfs(int node, int s = 1) {
    side[node] = s;
    for (int i : graph[node]) {
        if (!side[i]) dfs(i, 3 - s);
        else if (side[i] == s) {
            cout << "IMPOSSIBLE";
            exit(0);
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
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
        if (!side[i]) dfs(i);
    for (int i = 1; i <= n; i++)
        cout << side[i] << ' ';
}
