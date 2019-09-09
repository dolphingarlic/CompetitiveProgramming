#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[100001];
bool visited[100001];
int tin[100001], low[100001], deg[100001], timer = 1;

void dfs(int node, int parent = -1) {
    visited[node] = true;
    tin[node] = low[node] = timer++;

    for (int i : graph[node]) {
        if (i == parent) continue;
        if (visited[i]) low[node] = min(low[node], tin[i]);
        else {
            dfs(i, node);
            low[node] = min(low[node], low[i]);
            if (low[i] > tin[node]) deg[i]--, deg[node]--;
        }
    }
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
        deg[a]++, deg[b]++;
    }

    FOR(i, 1, n + 1) if (!visited[i]) dfs(i);

    FOR(i, 1, n + 1) if (deg[i] == 0) cout << i << '\n';
    return 0;
}