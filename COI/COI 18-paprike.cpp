/*
COI 2018 Paprike
- dp[i] = Minimum number of cuts for the subtree of i
- sm[i] = Minimum spiciness of the component containing i after cutting i's subtree dp[i] times
- We can greedily cut the children with largest sm[child] while sum(sm[child] + a[node]) > K
    - Notice how this always yields the smallest dp[node] and sm[node]
- Use a priority queue to keep track of the largest sm[child]
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, k;
ll a[100001];
vector<int> graph[100001];

int dfs(int node = 1, int parent = 0) {
    priority_queue<ll> pq;
    int ans = 0;
    for (int i : graph[node]) if (i != parent) {
        ans += dfs(i, node);
        pq.push(a[i]);
        a[node] += a[i];
    }
    while (a[node] > k) {
        ans++;
        a[node] -= pq.top();
        pq.pop();
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    FOR(i, 1, n + 1) cin >> a[i];
    FOR(i, 1, n) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    cout << dfs();
    return 0;
}