/*
CEOI 2015 Pipes
- Notice how we only care about the first K edges to form some BCC - further edges
  in that BCC change nothing, so we can simply discard them
- We can use 2 DSUs to keep track of (a) components and (b) nodes that are guaranteed
  to be in the same BCC
- This means we only store at most 2N - 2 edges
- We can then just run Tarjan's to get the bridges
- Complexity: O(M) time; O(N) memory
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int cmp1[100001], cmp2[100001];
vector<int> graph[100001];
bitset<100001> visited;
int tin[100001], low[100001], timer = 0;

int find(int A, int *cmp) {
    while (cmp[A] != A) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

bool onion(int A, int B, int *cmp) {
    if (find(A, cmp) == find(B, cmp)) return false;
    cmp[find(A, cmp)] = find(B, cmp);
    return true;
}

void dfs(int node, int parent = 0) {
    visited[node] = 1;
    tin[node] = low[node] = timer++;
    bool multi = false;
    for (int ptr = 0; ptr < graph[node].size(); ptr++) {
        int i = graph[node][ptr];
        if (i != parent || multi) {
            if (visited[i]) low[node] = min(low[node], tin[i]);
            else {
                dfs(i, node);
                low[node] = min(low[node], low[i]);
            }
        } else multi = true;
    }
    if (parent && tin[node] == low[node]) cout << node << ' ' << parent << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    iota(cmp1 + 1, cmp1 + n + 1, 1);
    iota(cmp2 + 1, cmp2 + n + 1, 1);
    while (m--) {
        int u, v;
        cin >> u >> v;
        if (onion(u, v, cmp1) || onion(u, v, cmp2)) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
    }
    for (int i = 1; i <= n; i++) if (!visited[i]) dfs(i);
    return 0;
}