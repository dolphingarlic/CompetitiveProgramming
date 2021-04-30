/*
CEOI 2012 Network
- First, decompose the graph into SCCs
- Since there's at most 1 path between any two nodes, the
  SCC graph is a directed tree
- We can use simple tree DP to find the number of reachable
  nodes for each node/SCC
- The minimum number of new links is the number of leaves
  in the tree
- To construct the answer, simply do this for each leaf L:
    - Find the lowest ancestor A with more than 1 child
    - Connect the "root" of L to the "root" of A
    - Delete the path A -> L from the SCC graph
- Complexity: O(N + M)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[100001], reversed[100001], stck;
bool visited[100001];
int cmp[100001], scc = 1, sz[100001], dp[100001];
int in_scc[100001], par[100001], c_cnt[100001]{0, 1};

void dfs1(int node) {
    visited[node] = true;
    for (int i : graph[node])
        if (!visited[i]) dfs1(i);
    stck.push_back(node);
}

void dfs2(int node) {
    cmp[node] = scc;
    sz[scc]++;
    for (int i : reversed[node]) {
        if (!cmp[i])
            dfs2(i);
        else if (cmp[i] != scc && !par[scc]) {
            in_scc[scc] = node;
            par[scc] = cmp[i];
            c_cnt[cmp[i]]++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, r;
    cin >> n >> m >> r;
    in_scc[1] = r;
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        reversed[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
        if (!visited[i]) dfs1(i);
    while (stck.size()) {
        if (!cmp[stck.back()]) {
            dfs2(stck.back());
            scc++;
        }
        stck.pop_back();
    }

    int leaves = 0;
    for (int i = scc - 1; i; i--) {
        if (!dp[i]) leaves++;
        dp[i] += sz[i];
        dp[par[i]] += dp[i];
    }

    for (int i = 1; i <= n; i++) cout << dp[cmp[i]] << ' ';
    cout << '\n';

    if (scc == 2)
        cout << 0;
    else {
        cout << leaves << '\n';
        for (int i = scc - 1; i; i--)
            if (dp[i] == sz[i]) {
                cout << in_scc[i] << ' ';
                int curr = par[i];
                while (true) {
                    c_cnt[curr]--;
                    if (c_cnt[curr]) {
                        cout << in_scc[curr] << '\n';
                        break;
                    }
                    curr = par[curr];
                }
            }
    }
    return 0;
}
