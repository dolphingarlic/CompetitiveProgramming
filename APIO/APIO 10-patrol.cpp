/*
APIO 2010 Patrol
- We essentially want to create the largest simple cycle with 1 or 2 edges
- First consider the k=1 case
    - Let dp[i] be the best in that subtree
    - Clearly this is the sum of the 2 "deepest" children's depths plus 2
    - This is essentially the largest loop we can make
- Next, we would probably want to find the second largest loop for k=2
    - Notice how if the 2 loops we find don't share an edge, this is correct
    - However, if they do share an edge, notice how that edge will be traversed twice
    - Because of this, we can simply negate all edges of the best loop found previously
      and run the dfs again to find the next biggest loop (taking edges traversed twice
      into consideration as well)
- Complexity: O(N log N) 
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
typedef long long ll;
using namespace std;

set<pair<int, int>> graph[100001];
pair<int, pair<int, int>> dp[100001];
pair<int, int> maxdepth[100001];

void dfs(int node = 1, int parent = 0) {
    pair<int, int> best = {0, 0}, next = {0, 0};

    for (pair<int, int> i : graph[node]) {
        if (i.x != parent) {
            dfs(i.x, node);

            if (maxdepth[i.x].x + i.y > best.x) {
                next = best;
                best = {maxdepth[i.x].x + i.y, i.x};
            } else if (maxdepth[i.x].x + i.y > next.x) {
                next = {maxdepth[i.x].x + i.y, i.x};
            }
        }
    }

    maxdepth[node] = best;
    dp[node] = {best.x + next.x, {best.y, next.y}};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    FOR(i, 1, n) {
        int a, b;
        cin >> a >> b;
        graph[a].insert({b, 1});
        graph[b].insert({a, 1});
    }

    dfs();
    if (k == 1) cout << 2 * (n - 1) + 1 - (*max_element(dp + 1, dp + n + 1)).x;
    else {
        int best_root = max_element(dp + 1, dp + n + 1) - dp;
        int ans = dp[best_root].x;

        for (int p = best_root, l = dp[best_root].y.x; l; p = l, l = maxdepth[l].y) {
            graph[p].erase({l, 1});
            graph[p].insert({l, -1});
        }
        for (int p = best_root, l = dp[best_root].y.y; l; p = l, l = maxdepth[l].y) {
            graph[p].erase({l, 1});
            graph[p].insert({l, -1});
        }

        dfs();
        cout << 2 * (n - 1) + 2 - ans - (*max_element(dp + 1, dp + n + 1)).x;
    }
    return 0;
}