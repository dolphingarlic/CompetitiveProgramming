/*
COCI 2016 Burza
- If K^2 > N, the answer is "DA"
- This means we effectively only need to solve for K <= 20
- We only really care about covering the nodes of depth K
    - Let these nodes be called leaves
- It's optimal to mark a node of depth i at step i
- Let (l[i], r[i]) = The leftmost and rightmost leaves node i covers
- dp[i][mask] = Can we cover the first i leaves using one node
                of each depth specified in the mask?
              = any(dp[l[k] - 1][mask ^ (1 << depth[k] - 1)]
                        if r[k] = i and mask & (1 << depth[k] - 1))
- Complexity: O(N 2^K) (amortised)
*/

#include <bits/stdc++.h>
using namespace std;

int n, k, depth[401], l[401], r[401], cnt = 0;
vector<int> graph[401], to_check[401];
bool dp[401][1 << 20];

void dfs(int node = 1, int parent = 0) {
    if (depth[node] == k) l[node] = r[node] = ++cnt;
    else {
        for (int i : graph[node]) if (i != parent) {
            depth[i] = depth[node] + 1;
            dfs(i, node);
            l[node] = min(l[node], l[i]);
            r[node] = max(r[node], r[i]);
        }
    }
    if (node != 1) to_check[r[node]].push_back(node);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    if (k * k > n) return cout << "DA", 0;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    memset(l, 0x3f, sizeof l);
    dfs();

    dp[0][0] = true;
    for (int i = 1; i <= cnt; i++) {
        for (int j = 0; j < (1 << k); j++) {
            for (int k : to_check[i]) {
                if (j & (1 << depth[k] - 1)) {
                    dp[i][j] |= dp[l[k] - 1][j ^ (1 << depth[k] - 1)];
                }
            }
        }
    }
    for (int i = 0; i < (1 << k); i++) {
        if (dp[cnt][i]) return cout << "DA", 0;
    }
    cout << "NE";
    return 0;
}