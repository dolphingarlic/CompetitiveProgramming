#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> graph[100001];
int grundy[100001];

void dfs(int node = 1, int parent = 0) {
    for (int i : graph[node]) if (i != parent) {
        dfs(i, node);
        grundy[node] ^= grundy[i] + 1;
    }
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
    dfs();
    cout << (grundy[1] ? "Alice" : "Bob");
    return 0;
}
