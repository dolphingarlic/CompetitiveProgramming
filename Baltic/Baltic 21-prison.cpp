/*
Baltic 2021 The short shank; Redemption
- Call prisoners with t[i] <= T "active" and others "passive"
- We basically want to maximize the number of passive prisoners
  that don't protest
- Consider a forest where:
    - The nodes are the passive prisoners
    - The parent of node i is the first prisoner to the right of
      i that won't rebel if there's a mattress to the left of i
- We can find this forest by sweeping through the prisoners and
  using a stack
    - We know that par[i] > j iff there exists some k in [i, j)
      where k + T - t[k] >= j, and suffix maximums are monotonic
- Next, we can just do the following D times:
    - Take the longest path in the forest from a root to a leaf
    - Subtract that path's length from the answer
    - Remove all nodes on that path from the graph
- Since we traverse each node at most once, this runs in
  O(N log N) time (if we use a priority queue to find the
  longest path efficiently)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int depth[2000001], mx_child[2000001];
vector<int> children[2000001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, d, tx;
    cin >> n >> d >> tx;

    int ans = n, glob_mx = 0, loc_mx = 0;
    priority_queue<pair<int, int>> pq;
    stack<pair<int, int>> stck;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        glob_mx = max(glob_mx, i + tx - t);
        loc_mx = max(loc_mx, i + tx - t);
        if (stck.size())
            stck.top().second = max(stck.top().second, loc_mx);
        if (t > tx) {
            if (glob_mx < i) ans--;
            else {
                depth[i] = 1;
                while (stck.size()) {
                    int node, tmp_mx;
                    tie(node, tmp_mx) = stck.top();
                    if (tmp_mx >= i) break;
                    children[i].push_back(node);
                    if (depth[node] + 1 > depth[i]) {
                        depth[i] = depth[node] + 1;
                        mx_child[i] = node;
                    }
                    stck.pop();
                    if (stck.size())
                        stck.top().second = max(stck.top().second, tmp_mx);
                }
                loc_mx = i + tx - t;
                stck.push({i, loc_mx});
            }
        }
    }
    while (stck.size()) {
        int root = stck.top().first;
        pq.push({depth[root], root});
        stck.pop();
    }

    while (d-- && pq.size()) {
        pair<int, int> curr = pq.top();
        pq.pop();
        ans -= curr.first;
        int node = curr.second;
        while (node) {
            for (int i : children[node]) if (i != mx_child[node])
                pq.push({depth[i], i});
            node = mx_child[node];
        }
    }
    cout << ans;
    return 0;
}