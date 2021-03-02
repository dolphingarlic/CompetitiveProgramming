/*
USACO 2021 Minimizing Edges
- If the graph is bipartite, the answer is N - 1
- Let's compute the shortest even and odd distances to each node
    - Let these be even[i] and odd[i]
- f(i, x) = True iff x = even[i] + 2k or odd[i] + 2k
- Consider a new graph where nodes store two numbers -- (even[i] + odd[i], max(even[i], odd[i]))
    - Arrange the nodes in a grid structure and group equal nodes together
- We can make these nodes "depend" on each other
- We say node i is "complete" if if depends on the node above it
    - Otherwise, it depends on the node to its left and right, so it's "incomplete"
- "Incomplete" nodes form chains that start with a complete node, so we can use DP
  to check which nodes to make "complete"
- Specifically, let dp1[i] = Best if node i is complete; dp2[i] = Best if node i is incomplete
- See the code for the details and transitions
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int INF = 1e6;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m, dub;
        cin >> n >> m;
        dub = 2 * n;
        vector<vector<int>> graph(dub);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            graph[u].push_back(v + n);
            graph[u + n].push_back(v);
            graph[v].push_back(u + n);
            graph[v + n].push_back(u);
        }
        vector<int> visited(dub);
        queue<int> q1;
        q1.push(0);
        visited[0] = 1;
        int ans = n - 1;
        while (q1.size()) {
            int curr = q1.front();
            q1.pop();
            for (int i : graph[curr]) if (!visited[i]) {
                q1.push(i);
                visited[i] = visited[curr] + 1;
            }
        }

        if (visited[n]) {
            map<pair<int, int>, int> cnt, dp1, dp2;
            for (int i = 0; i < n; i++) cnt[{visited[i] + visited[i + n], -max(visited[i], visited[i + n])}]++;
            pair<int, int> oob = {visited[0] + visited[n], -visited[0] - visited[n]};
            dp2[oob] = cnt[oob] = -1;

            for (auto i = next(cnt.begin()); i != cnt.end(); i++) {
                pair<int, int> curr;
                int freq;
                tie(curr, freq) = *i;
                pair<int, int> prv = {curr.first, curr.second - 1};

                // If both curr and prev(i)->first are "complete" nodes
                if (cnt.count({curr.first - 2, curr.second + 1})) {
                    if (curr.first == prev(i)->first.first)
                        dp1[curr] = freq + dp1[prev(i)->first];
                    else
                        dp1[curr] = freq + min(dp1[prev(i)->first], dp2[prev(i)->first]);
                } else dp1[curr] = INF;
                // If curr is "incomplete"
                if (cnt.count(prv)) {
                    dp2[curr] = min(dp1[prv], dp2[prv]) + max(cnt[prv], freq);
                    if (-curr.second * 2 == curr.first + 1) dp2[curr] += (freq + 1) / 2;
                } else dp2[curr] = INF;
            }

            cout << min(dp1.rbegin()->second, dp2.rbegin()->second) << '\n';
        } else {
            // The graph is bipartite
            cout << n - 1 << '\n';
        }
    }
    return 0;
}
