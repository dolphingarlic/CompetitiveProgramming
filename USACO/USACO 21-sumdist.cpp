/*
USACO 2021 Sum of Distances
- The distance to a K-tuple (v[1], v[2], ..., v[K]) from (1, 1, ..., 1) is
    min(max(1 -> v[i] where the path is even), max(1 -> v[i] where the path is odd))
- We can use a segtree/BIT + DP to compute sum(max(1 -> v[i] where the path is even) for each tuple)
    - First, sort the graphs by size
    - Let dp[i][j] be the number of i-tuples (i.e. from the first i graphs) with *even* distance j
    - First, compute dp[i][j] = sum(dp[i - 1][l] where l <= j)
    - Next, update dp[i][j] = (No. of even paths from node 1 in graph i of length < j) * dp[i - 1][j]
    - dp[K][j] will be the number of K-tuples with *even* distance j, so we can just iterate through dp[K]
- Similar logic holds for the odd-distance tuples
- What if a tuple can be reached in both even *and* odd distance though?
    - If that happens, then we overcount the path with length max(even[i], odd[i] for each i), so just do
      the above DP again but with maximums instead of evens/odds, and subtract that value from our answer
    - This is kinda like PIE
- Complexity: O(sum(N) log sum(N))
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

int k, n[50001], order[50001];
vector<ll> segtree[50001];

ll query(int a, int b, int tree, int node, int l, int r) {
    if (l > b || r < a) return 0;
    if (l >= a && r <= b) return segtree[tree][node];
    int mid = (l + r) / 2;
    return (query(a, b, tree, node * 2, l, mid) + query(a, b, tree, node * 2 + 1, mid + 1, r)) % MOD;
}

void update(int pos, ll val, int tree, int node, int l, int r) {
    if (l == r) segtree[tree][node] = (segtree[tree][node] + val) % MOD;
    else {
        int mid = (l + r) / 2;
        if (pos > mid) update(pos, val, tree, node * 2 + 1, mid + 1, r);
        else update(pos, val, tree, node * 2, l, mid);
        segtree[tree][node] = (segtree[tree][node * 2] + segtree[tree][node * 2 + 1]) % MOD;
    }
}

void reset(int tree) { segtree[tree].clear(); segtree[tree].resize(8 * n[tree]); }

ll compute_sum(vector<pair<int, int>> dists) {
    vector<vector<int>> graphs(k);
    for (pair<int, int> i : dists) graphs[i.second].push_back(i.first);
    
    reset(order[0]);
    for (int i : graphs[order[0]]) update(i, 1, order[0], 1, 0, 2 * n[order[0]] - 1);

    for (int i = 1; i < k; i++) {
        reset(order[i]);
        vector<int> pref(2 * n[order[i]], 0);
        for (int j : graphs[order[i]]) {
            update(j, query(0, j, order[i - 1], 1, 0, 2 * n[order[i - 1]] - 1), order[i], 1, 0, 2 * n[order[i]] - 1);
            pref[j]++;
        }
        for (int j = 1; j < 2 * n[order[i]]; j++) {
            pref[j] += pref[j - 1];
            update(j, pref[j - 1] * query(j, j, order[i - 1], 1, 0, 2 * n[order[i - 1]] - 1) % MOD, order[i], 1, 0, 2 * n[order[i]] - 1);
        }
    }

    ll ans = 0;
    for (int i = 1; i < 2 * n[order[k - 1]]; i++)
        ans = (ans + query(i, 2 * n[order[k - 1]] - 1, order[k - 1], 1, 0, 2 * n[order[k - 1]] - 1)) % MOD;
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> k;
    vector<pair<int, int>> even, odd, mx;
    for (int i = 0; i < k; i++) {
        order[i] = i;
        int m;
        cin >> n[i] >> m;
        vector<vector<int>> graph(2 * n[i]);
        vector<int> visited(2 * n[i]);
        while (m--) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            graph[u].push_back(n[i] + v);
            graph[v].push_back(n[i] + u);
            graph[n[i] + u].push_back(v);
            graph[n[i] + v].push_back(u);
        }
        // BFS to get even and odd distances
        visited[0] = 1;
        queue<int> q;
        q.push(0);
        while (q.size()) {
            int curr = q.front();
            q.pop();
            for (int j : graph[curr]) if (!visited[j]) {
                visited[j] = visited[curr] + 1;
                q.push(j);
            }
        }
        // Append to the distance lists
        for (int j = 0; j < n[i]; j++) {
            if (visited[j]) even.push_back({visited[j] - 1, i});
            if (visited[n[i] + j]) odd.push_back({visited[n[i] + j] - 1, i});
            if (visited[j] && visited[n[i] + j]) mx.push_back({max(visited[j], visited[n[i] + j]) - 1, i});
        }
    }
    sort(order, order + k, [](int a, int b) { return n[a] < n[b]; });
    cout << (compute_sum(even) + compute_sum(odd) - compute_sum(mx) + MOD) % MOD;
    return 0;
}
