/*
JOI 2014 Factories
- If there were very few queries, then we can do a simple tree DP to find min(dist to X + dist to Y) from each node
- Notice however that the only "important" nodes we need to check are on the virtual tree from (X union Y)
- We can thus construct the virtual tree for each query and then do tree DP on it to answer the query
- Complexity: O(V log N) where V = sum(S + T)
*/

#include "factories.h"

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 1e18;

vector<pair<int, ll>> graph[500000], vtree[500000];
int tin[500000], tout[500000], timer = 0, anc[500000][19];
ll to_anc[500000][19], to_X[500000], to_Y[500000];

void lca_dfs(int node = 0, int parent = -1) {
    tin[node] = timer++;
    for (int i = 1; i < 19; i++) {
        anc[node][i] = anc[anc[node][i - 1]][i - 1];
        to_anc[node][i] = to_anc[node][i - 1] + to_anc[anc[node][i - 1]][i - 1];
    }
    for (pair<int, ll> i : graph[node]) if (i.first != parent) {
        anc[i.first][0] = node;
        to_anc[i.first][0] = i.second;
        lca_dfs(i.first, node);
    }
    tout[node] = timer++;
}

inline bool is_ancestor(int u, int v) { return (tin[u] <= tin[v] && tout[u] >= tout[v]); }

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    for (int i = 18; ~i; i--) if (!is_ancestor(anc[u][i], v)) u = anc[u][i];
    return anc[u][0];
}

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

void Init(int N, int A[], int B[], int D[]) {
    for (int i = 0; i < N - 1; i++) {
        graph[A[i]].push_back({B[i], D[i]});
        graph[B[i]].push_back({A[i], D[i]});
    }
    lca_dfs();
    memset(to_X, 0x3f, sizeof to_X); memset(to_Y, 0x3f, sizeof to_Y);
}

bool cmp(int u, int v) { return tin[u] < tin[v]; }

ll ans;

void dfs1(int node, int parent = 0) {
    for (pair<int, ll> i : vtree[node]) if (i.first != parent) {
        dfs1(i.first, node);
        to_X[node] = min(to_X[node], to_X[i.first] + i.second);
        to_Y[node] = min(to_Y[node], to_Y[i.first] + i.second);
    }
}

void dfs2(int node, int parent = 0, ll par_to_X = INF, ll par_to_Y = INF) {
    to_X[node] = min(to_X[node], par_to_X);
    to_Y[node] = min(to_Y[node], par_to_Y);
    ans = min(ans, to_X[node] + to_Y[node]);
    for (pair<int, ll> i : vtree[node]) if (i.first != parent) {
        ll nxt_par_to_X = i.second + min(par_to_X, to_X[node]);
        ll nxt_par_to_Y = i.second + min(par_to_Y, to_Y[node]);
        dfs2(i.first, node, nxt_par_to_X, nxt_par_to_Y);
    }
}

ll Query(int S, int X[], int T, int Y[]) {
    vector<int> nodes;
    for (int i = 0; i < S; i++) {
        to_X[X[i]] = 0;
        nodes.push_back(X[i]);
    }
    for (int i = 0; i < T; i++) {
        to_Y[Y[i]] = 0;
        nodes.push_back(Y[i]);
    }
    sort(nodes.begin(), nodes.end(), cmp);
    for (int i = 1; i < S + T; i++) nodes.push_back(lca(nodes[i - 1], nodes[i]));
    sort(nodes.begin(), nodes.end(), cmp);
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
    vector<int> stck;
    for (int i : nodes) {
        while (stck.size() > 1 && !is_ancestor(stck.back(), i)) {
            int u = stck[stck.size() - 2], v = stck.back();
            vtree[u].push_back({v, dist(u, v)});
            stck.pop_back();
        }
        stck.push_back(i);
    }
    while (stck.size() > 1) {
        int u = stck[stck.size() - 2], v = stck.back();
        vtree[u].push_back({v, dist(u, v)});
        stck.pop_back();
    }
    ans = LLONG_MAX;
    dfs1(stck[0]);
    dfs2(stck[0]);
    for (int i : nodes) {
        to_X[i] = to_Y[i] = INF;
        vtree[i].clear();
    }
    return ans;
}
