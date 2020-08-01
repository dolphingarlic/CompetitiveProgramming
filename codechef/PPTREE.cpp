/*
codechef PPTREE
- xor of values from u to v = (xor of values from u to root) ^ (xor of values from v to root)
- This boils down to "find the maximum xor of 2 elements in an array"
- We construct this maximum xor greedily, from the greatest bit downward
- Complexity: O(N log MAX_VAL)
*/

#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> graph[100001];
int xor_val[100001];

void dfs(int node = 1, int parent = 0, int curr_xor = 0) {
    xor_val[node] = curr_xor;
    for (pair<int, int> i : graph[node]) if (i.first != parent)
        dfs(i.first, node, curr_xor ^ i.second);
}

int max_xor(int n) {
    int ans = 0, mask = 0;
    for (int b = 30; b >= 0; b--) {
        mask |= 1 << b;
        unordered_set<int> prefixes;
        for (int i = 1; i <= n; i++) prefixes.insert(mask & xor_val[i]);
        int pot_ans = ans | (1 << b);
        for (int i : prefixes) if (prefixes.count(pot_ans ^ i)) {
            ans = pot_ans;
            break;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) graph[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
        dfs();
        cout << max_xor(n) << '\n';
    }
    return 0;
}