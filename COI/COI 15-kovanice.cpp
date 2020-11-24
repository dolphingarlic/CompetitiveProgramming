/*
COI 2015 Kovanice
- Use DSU to merge all equal coins and draw directed edges between unequal ones
- The resulting graph is a DAG
- We know the weight of a coin iff it's part of a path of length N
- Simply DFS to find the depths and thus weights of each coin
- Complexity: O(M)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int cmp[300001];
vector<int> graph[300001];
int depth[300001], known[300001];

int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

void onion(int A, int B) { cmp[find(A)] = find(B); }

void depth_dfs(int node) {
    depth[node] = 1;
    for (int i : graph[node]) {
        if (!depth[i]) depth_dfs(i);
        depth[node] = max(depth[node], depth[i] + 1);
    }
}

void known_dfs(int node) {
    known[node] = depth[node];
    for (int i : graph[node]) {
        if (!known[i] && depth[i] == depth[node] - 1) known_dfs(i);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, v;
    cin >> n >> m >> v;
    iota(cmp + 1, cmp + m + 1, 1);
    vector<pair<int, int>> edges;
    while (v--) {
        int a, b;
        char c;
        cin >> a >> c >> b;
        if (c == '=') onion(a, b);
        else if (c == '<') edges.push_back({b, a});
        else edges.push_back({a, b});
    }
    for (pair<int, int> i : edges) graph[find(i.first)].push_back(find(i.second));
    for (int i = 1; i <= m; i++) if (i == find(i) && !depth[i]) depth_dfs(i);
    for (int i = 1; i <= m; i++) if (i == find(i) && depth[i] == n) known_dfs(i);
    for (int i = 1; i <= m; i++) {
        if (known[find(i)]) cout << 'K' << known[find(i)] << '\n';
        else cout << "?\n";
    }
    return 0;
}