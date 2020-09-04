/*
Baltic 2008 Gates
- 2-SAT
- Complexity: O(N + M)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> graph[1000000], reversed[1000000], stck;
bool visited[1000000], ans[500000];
int cmp[1000000];

void dfs1(int node) {
    visited[node] = true;
    for (int i : graph[node]) if (!visited[i]) dfs1(i);
    stck.push_back(node);
}

void dfs2(int node, int scc) {
    cmp[node] = scc;
    for (int i : reversed[node]) if (!cmp[i]) dfs2(i, scc);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int a, b;
        bool sa, sb;
        cin >> a >> sa >> b >> sb;
        a--, b--;
        graph[2 * a + !sa].push_back(2 * b + sb);
        graph[2 * b + !sb].push_back(2 * a + sa);
    }

    for (int i = 0; i < 2 * m; i++) if (!visited[i]) dfs1(i);
    for (int i = 0; i < 2 * m; i++) for (int j : graph[i]) reversed[j].push_back(i);
    int scc = 0;
    while (stck.size()) {
        if (!cmp[stck.back()]) dfs2(stck.back(), ++scc);
        stck.pop_back();
    }
    for (int i = 0; i < m; i++) {
        if (cmp[2 * i] == cmp[2 * i + 1]) return cout << "IMPOSSIBLE\n", 0;
        ans[i] = cmp[2 * i] < cmp[2 * i + 1];
    }
    for (int i = 0; i < m; i++) cout << ans[i] << '\n';
    return 0;
}