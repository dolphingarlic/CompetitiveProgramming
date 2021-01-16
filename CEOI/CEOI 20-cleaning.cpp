/*
CEOI 2020 Spring Cleaning
- It's possible to clean the tree if and only if the number of leaves is even
- The answer for a tree is
    (Number of edges) + (Number of nodes with an even number of leaves in subtree) - 1
- Notice how when we add a leaf node u to a non-leaf node v, it toggles the parity of
  the number of leaves for each node from v to the root of the tree
    - We can use a BIT to count the change in the answer for a single added leaf
- To handle more added leaves, construct the virtual tree from each non-leaf node in
  the query (including previously-leaf nodes that became non-leaf nodes)
- Each node in the virtual tree contributes exactly
    (Number of added leaves in subtree is even) * (Change in answer on path from node to parent)
  to the change in the answer
- Complexity: O(S log N) where S = sum(D)
*/

#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<int> graph[100001];
int leaves[100001], tot_leaves = 0, bad = 0;
bool is_leaf[100001];
int tin[100001], tout[100001], timer = 0, anc[100001][18];

vector<int> vtree[100001];
int ans, bit[100001];
int a[100001], l_delta[100001];

void update(int pos, int val) { for (; pos <= n; pos += pos & -pos) bit[pos] += val; }

int query(int l, int r) {
    int res = 0;
    for (; r; r -= r & -r) res += bit[r];
    for (l--; l; l -= l & -l) res -= bit[l];
    return res;
}

void lca_dfs(int node, int parent = 0) {
    // LCA stuff
    tin[node] = ++timer;
    for (int i = 1; i < 18; i++) anc[node][i] = anc[anc[node][i - 1]][i - 1];
    // Check whether it's a leaf
    if (graph[node].size() == 1) {
        leaves[node] = 1;
        tot_leaves++;
        is_leaf[node] = true;
    }
    // DFS on children
    for (int i : graph[node]) if (i != parent) {
        anc[i][0] = node;
        lca_dfs(i, node);
        leaves[node] += leaves[i];
    }
    tout[node] = timer;
    // Set what happens when we toggle the parity
    if (leaves[node] & 1) update(tin[node], 1), update(tout[node] + 1, -1);
    else {
        update(tin[node], -1), update(tout[node] + 1, 1);
        bad++;
    }
}

bool is_ancestor(int u, int v) { return tin[u] <= tin[v] && tout[u] >= tout[v]; }

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    for (int i = 17; ~i; i--) if (anc[u][i] && !is_ancestor(anc[u][i], v)) u = anc[u][i];
    return anc[u][0];
}

void vtree_dfs(int node, int parent = 0) {
    for (int i : vtree[node]) if (i != parent) {
        vtree_dfs(i, node);
        l_delta[node] += l_delta[i];
    }
    ans += (l_delta[node] & 1) * query(tin[parent] + 1, tin[node]);
}

bool cmp(int u, int v) { return tin[u] < tin[v]; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) if (graph[i].size() > 1) {
        lca_dfs(i);
        break;
    }

    while (q--) {
        // Read query data and update original tree
        int d;
        cin >> d;
        vector<int> nodes;
        for (int i = 0; i < d; i++) {
            cin >> a[i];
            if (is_leaf[a[i]]) is_leaf[a[i]] = false;
            else {
                leaves[a[i]]++;
                tot_leaves++;
                l_delta[a[i]]++;
                nodes.push_back(a[i]);
            }
        }

        // Construct the virtual tree
        sort(nodes.begin(), nodes.end(), cmp);
        int m = nodes.size();
        for (int i = 1; i < m; i++) nodes.push_back(lca(nodes[i - 1], nodes[i]));
        sort(nodes.begin(), nodes.end(), cmp);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        
        vector<int> stck;
        for (int i : nodes) {
            while (stck.size() > 1 && !is_ancestor(stck.back(), i)) {
                vtree[stck[stck.size() - 2]].push_back(stck.back());
                stck.pop_back();
            }
            stck.push_back(i);
        }
        while (stck.size() > 1) {
            vtree[stck[stck.size() - 2]].push_back(stck.back());
            stck.pop_back();
        }

        // Compute and output the answer
        if (tot_leaves & 1) cout << "-1\n";
        else {
            ans = n + d + bad - 2;
            if (stck.size()) vtree_dfs(stck[0]);
            cout << ans << '\n';
        }

        // Reset the original tree
        for (int i = 0; i < d; i++) {
            if (leaves[a[i]] == 1) is_leaf[a[i]] = true;
            else {
                leaves[a[i]]--;
                tot_leaves--;
            }
        }

        // Reset the vtree
        for (int i : nodes) {
            vtree[i].clear();
            l_delta[i] = 0;
        }
    }
    return 0;
}