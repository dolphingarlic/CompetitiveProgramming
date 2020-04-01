/*
Baltic 2015 File Paths
- View this problem as a tree. For convenience, increase all lengths (including S) by 1
- Let A->B denote the path length from A to B
- There are 3 cases to check whether we can force some path from Root->V to equal K
- Case 1: Root->V == K
- Case 2: There exist X, Y, and an integer P such that X is an ancestor of Y and V and
  Root->V + P * (X->Y + S) == K
- Case 3: There exist X and Y such that X is an ancestor of V and
  Root->Y + S + X->V == K
- First, compute for each node V, Root->V
- Using this, we can easily check case 1
- For case 3, we simply check for each ancestor A of V whether there exists Y such that
  Root->Y + S + A->V == K
    - A->V == Root->V - Root->A
- For case 2, we do a DFS
    - Since X must be an ancestor of V, when we enter a node X, for each child C, mark X->C
      as available. When we leave X, unmark the same values
    - Notice how each pair (X, C) is only marked/unmarked once, so it's efficient
    - Then just check for each factor of K - Root->V whether it's marked
- Complexity: O(N^2)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m, k, s;
vector<int> graph[6060];
int to_root[6060], par[6060], can[2020202], cyc[2020202];
bool good[6060];

void add_cycles(int node, int root, int val) {
    cyc[to_root[node] - to_root[root] + s] += val;
    for (int i : graph[node]) if (i <= n) add_cycles(i, root, val);
}

void dfs(int node = 0) {
    if (node > n) {
        int add_dist = k - to_root[node];
        if (!add_dist) good[node] = true;
        for (int i = 1; i * i <= add_dist; i++)
            if (add_dist % i == 0 && (cyc[i] || cyc[add_dist / i])) good[node] = true;
        for (int i = par[node]; ~i; i = par[i])
            if (add_dist - s + to_root[i] >= 0 && can[add_dist - s + to_root[i]]) good[node] = true;
    }
    add_cycles(node, node, 1);
    for (int i : graph[node]) dfs(i);
    add_cycles(node, node, -1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k >> s;
    s++;
    par[0] = -1;
    can[0] = 1;
    FOR(i, 1, n + m + 1) {
        int l;
        cin >> par[i] >> l;
        graph[par[i]].push_back(i);
        to_root[i] = to_root[par[i]] + l + 1;
        if (i <= n) can[to_root[i]]++;
    }
    dfs();

    FOR(i, n + 1, n + m + 1) cout << (good[i] ? "YES\n" : "NO\n");
    return 0;
}