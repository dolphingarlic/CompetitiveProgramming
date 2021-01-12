/*
JOI 2014 Factories
- Let's focus on a single query for now
- For each node, the optimal path either visits it or is completely inside one of its children's subtrees
- This gives us the following algorithm:
    - First, perform a centroid decomposition on the tree
    - Next, for each node u in X, traverse up the centroid tree and update c_dist[v] = min(c_dist[v], dist(u->v))
    - Finally, the answer is min(c_dist[v] + dist(u->v) : u in Y, v is an ancestor of u in the centroid tree)
    - (Also reset c_dist after each query)
- Centroid decomposition is O(N log N) and each query is O((S + T) log^2 N)
- Complexity: O(N log N + V log^2 N) where V = sum(S) + sum(T)
*/

#include "factories.h"

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 1e18;

vector<pair<int, int>> graph[500000];
int tin[500000], tout[500000], timer = 0, anc[500000][19];
ll to_anc[500000][19];
bool processed[500000];
int subtree[500000], c_par[500000];
ll c_dist[500000];

void dfs(int node = 0, int parent = -1) {
    tin[node] = timer++;
    for (int i = 1; i < 19; i++) {
        anc[node][i] = anc[anc[node][i - 1]][i - 1];
        to_anc[node][i] = to_anc[node][i - 1] + to_anc[anc[node][i - 1]][i - 1];
    }
    for (pair<int, int> i : graph[node]) if (i.first != parent) {
        anc[i.first][0] = node;
        to_anc[i.first][0] = i.second;
        dfs(i.first, node);
    }
    tout[node] = timer++;
}

inline bool is_ancestor(int u, int v) { return (tin[u] <= tin[v] && tout[u] >= tout[v]); }

ll dist(int u, int v) {
    ll ans = 0;
    for (int i = 18; ~i; i--) if (!is_ancestor(anc[u][i], v)) {
        ans += to_anc[u][i];
        u = anc[u][i];
    }
    if (!is_ancestor(u, v)) ans += to_anc[u][0];
    for (int i = 18; ~i; i--) if (!is_ancestor(anc[v][i], u)) {
        ans += to_anc[v][i];
        v = anc[v][i];
    }
    if (!is_ancestor(v, u)) ans += to_anc[v][0];
    return ans; 
}

void get_subtree_sizes(int node, int parent = -1) {
    subtree[node] = 1;
    for (pair<int, int> i : graph[node]) if (i.first != parent && !processed[i.first]) {
        get_subtree_sizes(i.first, node);
        subtree[node] += subtree[i.first];
    }
}

int get_centroid(int node, int parent, int tree_size) {
    for (pair<int, int> i : graph[node])
        if (i.first != parent && !processed[i.first] && subtree[i.first] > tree_size)
            return get_centroid(i.first, node, tree_size);
    return node;
}

void centroid_decomp(int node = 0, int prv_centroid = -1) {
    get_subtree_sizes(node);
    int centroid = get_centroid(node, -1, subtree[node] >> 1);
    c_par[centroid] = prv_centroid;
    processed[centroid] = true;
    for (pair<int, int> i : graph[centroid]) if (!processed[i.first])
        centroid_decomp(i.first, centroid);
}

void Init(int N, int A[], int B[], int D[]) {
    for (int i = 0; i < N - 1; i++) {
        graph[A[i]].push_back({B[i], D[i]});
        graph[B[i]].push_back({A[i], D[i]});
    }
    dfs();
    centroid_decomp();
    memset(c_dist, 0x3f, sizeof c_dist);
}

ll Query(int S, int X[], int T, int Y[]) {
    for (int i = 0; i < S; i++) {
        int curr = X[i];
        while (curr != -1) {
            c_dist[curr] = min(c_dist[curr], dist(X[i], curr));
            curr = c_par[curr];
        }
    }
    ll ans = INF;
    for (int i = 0; i < T; i++) {
        int curr = Y[i];
        while (curr != -1) {
            ans = min(ans, c_dist[curr] + dist(Y[i], curr));
            curr = c_par[curr];
        }
    }
    for (int i = 0; i < S; i++) {
        int curr = X[i];
        while (curr != -1) {
            c_dist[curr] = INF;
            curr = c_par[curr];
        }
    }
    return ans;
}
