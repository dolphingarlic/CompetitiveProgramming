/*
COI 2019 Izlet
- Let A be the matrix given
- We start with a tree with node 1 and build it recursively with DFS
- For the current node v...
    - First, connect all unvisited nodes u with v where A[v][u] == 1,
      make them the same colour as v, and mark them as visited
    - Next, for each unvisited node u where A[v][u] == 2...
        - Connect u with v
        - Find the node w already in the tree such that A[v][w] == A[u][w]
          and u->w is of minimal length
        - If w exists, then make u the same colour as w
        - Otherwise, make u a new colour
        - DFS on u
- Convince yourself that this works because I'm not proving it
- Complexity: O(N^2)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int k, n, a[3001][3001], apsp[3001][3001];
int colour[3001], c = 1, e = 1;
bool visited[3001];
vector<int> in_tree;
pair<int, int> edges[3001];
 
void dfs(int node = 1) {
    visited[node] = true;
    in_tree.push_back(node);
 
    FOR(i, 1, n + 1) if (!visited[i] && a[node][i] == 1) {
        visited[i] = true;
        colour[i] = colour[node];
        for (int j : in_tree) apsp[i][j] = apsp[j][i] = apsp[node][j] + 1;
        edges[e++] = {node, i};
    }
 
    FOR(i, 1, n + 1) if (!visited[i] && a[node][i] == 2) {
        int mn_same = 0;
        for (int j : in_tree) {
            apsp[i][j] = apsp[j][i] = apsp[node][j] + 1;
            if (a[i][j] == a[node][j] && (!mn_same || apsp[i][j] < apsp[i][mn_same])) mn_same = j;
        }
        if (mn_same) colour[i] = colour[mn_same];
        else colour[i] = ++c;
        edges[e++] = {node, i};
        dfs(i);
    }
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> k >> n;
    FOR(i, 1, n + 1) FOR(j, 1, n + 1) cin >> a[i][j];
    colour[1] = 1;
    dfs();
 
    FOR(i, 1, n + 1) cout << colour[i] << ' ';
    cout << '\n';
    FOR(i, 1, n) cout << edges[i].first << ' ' << edges[i].second << '\n';
    return 0;
}