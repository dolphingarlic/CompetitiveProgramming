#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[200001];
int ans[200001];

void dfs(int node, int k = 1) {
    ans[node] = k;
    for (int i : graph[node]) if (!ans[i]) dfs(i, 3 - k);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, m) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    FOR(i, 1, n + 1) {
        if (!graph[i].size()) return cout << "NIE\n", 0;
        if (!ans[i]) dfs(i);
    }

    cout << "TAK\n";
    FOR(i, 1, n + 1) cout << (ans[i] == 1 ? "K\n" : "S\n");
    return 0;
}