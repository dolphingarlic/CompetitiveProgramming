/*
IOI 2017 Simurgh
- Clearly, bridges must be in the golden set
- Lemma 1: Given a cycle C, we can determine whether each edge in C is in the golden set
  in |C| queries
    - First, find the DFS tree
    - Next, for each edge E in C, take C \ E and "union" it with the DFS tree, and query it
    - For any edge with (query answer) < (maximum query answer), we know that it's in the
      golden set because at least one of the edges in C isn't in the golden set
- Using lemma 1, we can check each edge in the DFS tree in 2N queries
    - Some optimizations (e.g. checking an edge at most twice) are needed; see the code
- Lemma 2: We can count the number of common roads in any forest in 1 query
    - Similarly to before, take the forest and "union" it with the DFS tree
    - The answer is (query result) - (no. of golden roads from the DFS tree in our query)
- Using lemma 2, we can find the degree of each node in the golden tree in N queries
- We can then binary search for each node's parent, starting at the leaves
- 3N + N log N queries
*/

#include "simurgh.h"

#include <bits/stdc++.h>
using namespace std;

int n, m, u[124750], v[124750];
vector<pair<int, int>> graph[500];
int tin[500], low[500], timer = 0, deg[500], cmp[500];
bool visited[500], known[124750], is_golden[124750];
pair<int, int> back_edge[500], par[500];
vector<int> dfs_tree;

void dfs(int node = 0, int parent = -1) {
    visited[node] = true;
    tin[node] = low[node] = timer++;
    for (pair<int, int> i : graph[node]) if (i.first != parent) {
        if (visited[i.first]) {
            low[node] = min(low[node], tin[i.first]);
            if (tin[node] > tin[i.first]) {
                if (back_edge[node].first == -1 || tin[back_edge[node].first] > tin[i.first])
                    back_edge[node] = i;
            }
        } else {
            dfs(i.first, node);
            low[node] = min(low[node], low[i.first]);
            if (low[i.first] > tin[node])
                known[i.second] = is_golden[i.second] = true;
            dfs_tree.push_back(i.second);
            par[i.first] = {node, i.second};
        }
    }
}

int find(int A) { return cmp[A] = (A == cmp[A] ? A : find(cmp[A])); }
void onion(int A, int B) { cmp[find(A)] = find(B); }

int query_forest(vector<int> forest) {
    iota(cmp, cmp + n, 0);
    for (int i : forest) onion(u[i], v[i]);
    int delta = 0;
    for (int i : dfs_tree) if (find(u[i]) != find(v[i])) {
        delta -= is_golden[i];
        forest.push_back(i);
        onion(u[i], v[i]);
    }
    return count_common_roads(forest) + delta;
}

vector<int> find_roads(int _n, vector<int> _u, vector<int> _v) {
    n = _n, m = _u.size();
    for (int i = 0; i < m; i++) {
        u[i] = _u[i], v[i] = _v[i];
        graph[u[i]].push_back({v[i], i});
        graph[v[i]].push_back({u[i], i});
    }
    // First, we find the status of all edges in the DFS tree
    fill_n(back_edge, n, make_pair(-1, -1));
    dfs();
    int dfs_tree_common = count_common_roads(dfs_tree);
    for (int i = 0; i < n; i++) if (~back_edge[i].first) {
        int curr = i;
        bool single_known = false;
        vector<int> unknown;
        while (curr != back_edge[i].first) {
            if (!known[par[curr].second])
                unknown.push_back(par[curr].second);
            else if (!single_known) {
                single_known = true;
                unknown.push_back(par[curr].second);
            }
            curr = par[curr].first;
        }
        if (unknown.size() == 1) continue;
        
        vector<int> query_res;
        for (int j : unknown) {
            vector<int> to_query = {back_edge[i].second};
            for (int k : dfs_tree) if (k != j) to_query.push_back(k);
            query_res.push_back(count_common_roads(to_query));
        }

        int mx = max(dfs_tree_common, *max_element(query_res.begin(), query_res.end()));
        for (int i = 0; i < unknown.size(); i++) {
            known[unknown[i]] = true;
            is_golden[unknown[i]] = (query_res[i] != mx);
        }
    }
    // Next, we get the "degree" of each node in the golden tree
    queue<int> q;
    for (int i = 0; i < n; i++) {
        vector<int> to_query;
        for (pair<int, int> j : graph[i]) to_query.push_back(j.second);
        deg[i] = query_forest(to_query);
        if (deg[i] == 1) q.push(i);
    }
    // Finally, binary search for the "parent" of each node
    while (q.size()) {
        int curr = q.front();
        q.pop();
        if (deg[curr] != 1) continue;
        int l = 0, r = graph[curr].size() - 1;
        while (l != r) {
            int mid = (l + r) / 2;
            vector<int> to_query;
            for (int i = l; i <= mid; i++) to_query.push_back(graph[curr][i].second);
            if (query_forest(to_query)) r = mid;
            else l = mid + 1;
        }
        int nxt, id;
        tie(nxt, id) = graph[curr][l];
        is_golden[id] = true;
        deg[nxt]--;
        if (deg[nxt] == 1) q.push(nxt);
        vector<pair<int, int>> tmp;
        for (pair<int, int> i : graph[nxt]) if (i.second != id) tmp.push_back(i);
        graph[nxt] = tmp;
    }
    // Return the answer
    vector<int> ans;
    for (int i = 0; i < m; i++) if (is_golden[i]) ans.push_back(i);
    return ans;
}
