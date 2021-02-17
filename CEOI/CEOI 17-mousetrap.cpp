/*
CEOI 2017 Mousetrap
- Consider the chain of nodes between M and T - we only really care about these
- Dumbo's optimal strategy will be of the following form:
    1) Block incident edges on the chain to force the mouse into one of the
       chain nodes' subtrees
    2) Block edges in that subtree until the mouse reaches a leaf
    3) While the mouse is trapped, block all remaining incident edges on the chain
       that the mouse can reach to stop the mouse from going into more subtrees
    4) Clean all edges in the subtree containing the mouse
    5) The mouse has no choice but to run into the mousetrap now
- To determine which edges to block in the subtree, let dp[i] = The minimum number
  of moves Dumbo needs to trap the mouse if it goes down from node i (tree rooted at T)
- dp[i] = graph[i].size() - 1 + (second largest dp[c] for c in i's children)
- Setting the answer to dp[M] + (number of incident edges on the chain) solves the first
  two subtasks, but the answer may be more than that: what if the mouse moves up the
  chain and goes into one of those nodes' subtrees?
- To handle this case, we can binary search for the answer, greedily block all "bad"
  edges, and then check that we have enough moves to do so
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, t, m, c;
vector<int> graph[1000001], chain;
ll dp[1000001], pref[1000001];
bool in_chain[1000001];

bool dfs(int node = t, int parent = 0) {
    ll mx1 = 0, mx2 = 0;
    for (int i : graph[node]) if (i != parent) {
        in_chain[node] |= dfs(i, node);
        if (dp[i] >= mx1) mx2 = mx1, mx1 = dp[i];
        else if (dp[i] > mx2) mx2 = dp[i];
    }
    sort(graph[node].begin(), graph[node].end(), [](int A, int B) { return dp[A] > dp[B]; });
    dp[node] = graph[node].size() - 1 + mx2;
    if (in_chain[node]) chain.push_back(node);
    return in_chain[node];
}

bool check(int mn) {
    int rem = 1, used = 0;
    for (int i = c - 1; i; i--, rem++) {
        int allowed = mn - pref[i] - used;
        for (int j : graph[chain[i]]) if (!in_chain[j]) {
            if (dp[j] <= allowed) break;
            if (!rem) return false;
            rem--, used++;
        }
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> t >> m;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    in_chain[m] = true;
    dfs();
    reverse(chain.begin(), chain.end());
    c = chain.size();
    for (int i = 1; i < c; i++)
        pref[i] = pref[i - 1] + graph[chain[i]].size() - 2 + (i == c - 1);

    int l = pref[c - 1], r = n - 1;
    while (l != r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l;
    return 0;
}
