#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<pair<int, int>> graph[100001];
int nxt[100001], cmp[100001];
bool visited[100001], used[200001], processed[100001];
vector<vector<int>> cycles_on[100001];

int find(int A) { return cmp[A] = (A == cmp[A] ? A : find(cmp[A])); }
void onion(int A, int B) { cmp[find(A)] = find(B); }

void dfs(int node = 1) {
    if (visited[node]) {
        int start = node;
        cycles_on[start].push_back({});
        while (visited[node]) {
            visited[node] = false;
            cycles_on[start].back().push_back(node);
            node = nxt[node];
        }
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

void process(int node) {
    if (!processed[node]) {
        processed[node] = true;
        for (auto &i : cycles_on[node]) {
            for (int j : i) process(j);
        }
    }
    cout << node << ' ';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    iota(cmp + 1, cmp + n + 1, 1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, m});
        graph[v].push_back({u, m});
        onion(u, v);
    }
    for (int i = 1; i <= n; i++)
        if ((graph[i].size() & 1) || (graph[i].size() && find(i) != find(1)))
            return cout << "IMPOSSIBLE", 0;
    dfs();
    process(1);
    return 0;
}