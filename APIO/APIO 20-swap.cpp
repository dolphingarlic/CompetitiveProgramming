/*
APIO 2020 Swap
- First, sort the edges in increasing order of weight
- We effectively want to find the edge with weight W such that
  if we consider the graph with only edges with weight <= W, then
  the connected component with X and Y (assuming it exists) has
  a cycle or a node with degree >= 3
- Construct the DSU tree using the edges (creating a new node in
  the tree for each edge)
    - The subtree of any node (which represents some edge)
      represents the connected component containing that edge
      at that point of the DSU
- We also store whether that connected component has a cycle or
  node with degree >= 3 at that point
    - Merging is easy, since we never destroy cycles or decrease degree
- For a query on (X, Y), we want to find the lowest node in the DSU tree
  such that it's an ancestor of both X and Y and the connected component
  that it's in has a cycle or a node with degree >= 3 at that point
- We can use LCA and binary jumping to find that node
- Complexity: O((N + M) log (N + M))
*/

#include "swap.h"

#include <bits/stdc++.h>
using namespace std;

pair<int, pair<int, int>> edges[200000];
int cmp[300000], deg[300000], cost[300000], nodes;
bool has_deg_3[300000], has_cycle[300000];
vector<int> dsu_tree[300000];
int tin[300000], tout[300000], timer = 0, anc[300000][20];

int find(int A) {
    while (A != cmp[A]) A = cmp[A], cmp[A] = cmp[cmp[A]];
    return A;
}

void onion(int A, int B) {
    has_cycle[nodes] = has_cycle[find(A)] || has_cycle[find(B)];
    if (find(A) == find(B)) has_cycle[nodes] = true;
    has_deg_3[nodes] = has_deg_3[find(A)] || has_deg_3[find(B)];
    if (deg[A] == 3 || deg[B] == 3) has_deg_3[nodes] = true;
    dsu_tree[nodes].push_back(find(A));
    if (find(A) != find(B)) dsu_tree[nodes].push_back(find(B));
    cmp[find(A)] = cmp[find(B)] = nodes;
    nodes++;
}

void dfs(int node = nodes - 1, int parent = -1) {
    tin[node] = timer++;
    for (int i = 1; i < 20; i++) anc[node][i] = -1;
    for (int i = 1; i < 20 && ~anc[node][i - 1]; i++) anc[node][i] = anc[anc[node][i - 1]][i - 1];
    for (int i : dsu_tree[node]) {
        anc[i][0] = node;
        dfs(i, node);
    }
    tout[node] = timer++;
}

bool is_ancestor(int A, int B) { return tin[A] <= tin[B] && tout[A] >= tout[B]; }

int lca(int A, int B) {
    if (is_ancestor(A, B)) return A;
    for (int i = 19; ~i; i--) if (~anc[A][i] && !is_ancestor(anc[A][i], B)) A = anc[A][i];
    return anc[A][0];
}

void init(int N, int M, vector<int> U, vector<int> V, vector<int> W) {
    for (int i = 0; i < M; i++) edges[i] = {W[i], {U[i], V[i]}};
    sort(edges, edges + M);
    nodes = N;
    iota(cmp, cmp + N + M, 0);
    for (int i = 0; i < M; i++) {
        deg[edges[i].second.first]++;
        deg[edges[i].second.second]++;
        cost[nodes] = edges[i].first;
        onion(edges[i].second.first, edges[i].second.second);
    }
    for (int i = 0; i < nodes; i++) for (int j = 0; j < 20; j++) anc[i][j] = -1;
    dfs();
}

int getMinimumFuelCapacity(int X, int Y) {
    if (!has_cycle[nodes - 1] && !has_deg_3[nodes - 1]) return -1;
    int l = lca(X, Y);
    if (has_cycle[l] || has_deg_3[l]) return cost[l];
    for (int i = 19; ~i; i--) if (~anc[l][i] && !has_cycle[anc[l][i]] && !has_deg_3[anc[l][i]])
        l = anc[l][i];
    return cost[anc[l][0]];
}