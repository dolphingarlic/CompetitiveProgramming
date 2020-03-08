/*
COCI 2020 Skandi
- If we view horizontal and vertical words as nodes in a graph and connect words if they intersect,
  we get a bipartite graph
- The problem now becomes finding the minimum vertex cover of this graph
    - By Konig's theorem, this is equal to the maximum bipartite matching
    - We can use the Hopcraft-Karp algorithm for this
    - To construct the vertex cover, we do a DFS and magic happens
- Complexity: O(N^3)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
bool dfs(int a, int L, vector<vector<int>>& g, vector<int>& btoa, vector<int>& A, vector<int>& B) {
    if (A[a] != L) return 0;
    A[a] = -1;
    for (int b : g[a]) if (B[b] == L + 1) {
        B[b] = 0;
        if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
            return btoa[b] = a, 1;
    }
    return 0;
}
 
int hopcroftKarp(vector<vector<int>>& g, vector<int>& btoa) {
    int res = 0;
    vector<int> A(g.size()), B(btoa.size()), cur, next;
    for (;;) {
        fill(A.begin(), A.end(), 0);
        fill(B.begin(), B.end(), 0);
        /// Find the starting nodes for BFS (i.e. layer 0).
        cur.clear();
        for (int a : btoa) if(a != -1) A[a] = -1;
        FOR(a, 0, g.size()) if(A[a] == 0) cur.push_back(a);
        /// Find all layers using bfs.
        for (int lay = 1;; lay++) {
            bool islast = 0;
            next.clear();
            for (int a : cur) for (int b : g[a]) {
                if (btoa[b] == -1) {
                    B[b] = lay;
                    islast = 1;
                }
                else if (btoa[b] != a && !B[b]) {
                    B[b] = lay;
                    next.push_back(btoa[b]);
                }
            }
            if (islast) break;
            if (next.empty()) return res;
            for (int a : next) A[a] = lay;
            cur.swap(next);
        }
        /// Use DFS to scan for augmenting paths.
        FOR(a, 0, g.size())
            res += dfs(a, 0, g, btoa, A, B);
    }
}
 
char grid[501][501];
int c_horiz[501][501], c_vert[501][501], horiz = 0, vert = 0;
vector<pair<int, int>> horiz_loc, vert_loc;
bool visited[500001], has_edge[250001];
vector<int> graph[500001];
 
void fvc(int node) {
    visited[node] = true;
    for (int i : graph[node]) if (!visited[i]) fvc(i);
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        cin >> grid[i][j];
        if (grid[i][j] == '0') {
            if (grid[i][j - 1] == '1') {
                c_horiz[i][j] = horiz++;
                horiz_loc.push_back({i, j - 1});
            } else c_horiz[i][j] = c_horiz[i][j - 1];
 
            if (grid[i - 1][j] == '1') {
                c_vert[i][j] = vert++;
                vert_loc.push_back({i - 1, j});
            } else c_vert[i][j] = c_vert[i - 1][j];
        }
    }
 
    vector<vector<int>> g(vert);
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        if (grid[i][j] == '0') g[c_vert[i][j]].push_back(c_horiz[i][j]);
    }
 
    vector<int> btoa(horiz, -1);
    cout << hopcroftKarp(g, btoa) << '\n';
 
    FOR(i, 0, vert) for (int j : g[i]) {
        if (btoa[j] == i) {
            graph[vert + j].push_back(i);
            has_edge[i] = true;
        } else graph[i].push_back(vert + j);
    }
 
    FOR(i, 0, vert) if (!has_edge[i] && !visited[i]) fvc(i);
    FOR(i, 0, vert) if (!visited[i]) cout << vert_loc[i].first << ' ' << vert_loc[i].second << " DOLJE\n";
    FOR(i, 0, horiz) if (visited[vert + i]) cout << horiz_loc[i].first << ' ' << horiz_loc[i].second << " DESNO\n";
    return 0;
}