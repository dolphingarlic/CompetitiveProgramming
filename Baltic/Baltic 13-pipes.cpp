/*
Baltic 2013 Pipes
- Firstly, notice that nodes with degree 1 uniquely determine their edges
    - While there are nodes with degree 1, solve their edges and remove them
- Now we are left with some connected component (or none in the case of a tree)
- Notice how the answer is not unique when there is an even cycle
- Notice how the answer is not unique when we have an "hourglass"
  i.e. 2 odd cycles joined by some number of edges (possibly 0)
    - Just draw it out and convince yourself this is true
- This means the resulting graph must be a single odd cycle to have a unique solution
- Solve for 1 edge in this cycle and then do step 1 again (i.e. removing degree 1 nodes)
- Complexity: O(N) or O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m;
set<pair<int, int>> graph[100001];
int c[100001], ans[500001], visited[100001], alt_sum = 0;

void dfs(int node, int parity = 1) {
    visited[node] = parity;
    for (pair<int, int> i : graph[node]) if (!visited[i.first]) {
        dfs(i.first, 3 - parity);
        if (parity == 1) alt_sum += c[i.first];
        else alt_sum -= c[i.first];
    }
}

void compress() {
    queue<int> leaves;
    FOR(i, 1, n + 1) if (graph[i].size() == 1) leaves.push(i);
    while (leaves.size()) {
        int curr = leaves.front();
        leaves.pop();
        for (pair<int, int> i : graph[curr]) {
            graph[i.first].erase({curr, i.second});
            ans[i.second] = 2 * c[curr];
            c[i.first] -= c[curr];

            if (graph[i.first].size() == 1) leaves.push(i.first);
        }
        graph[curr].clear();
    }
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, n + 1) cin >> c[i];
    FOR(i, 1, m + 1) {
        int x, y;
        cin >> x >> y;
        graph[x].insert({y, i});
        graph[y].insert({x, i});
    }

    compress();

    int cnt = 0;
    FOR(i, 1, n + 1) {
        if (graph[i].size() > 2) return cout << 0, 0;
        if (graph[i].size() == 2) cnt++;
    }
    if (cnt != 0 && !(cnt & 1)) return cout << 0, 0;

    FOR(i, 1, n + 1) if (graph[i].size() == 2) {
        dfs(i);
        int x = (*graph[i].begin()).first, y = (*graph[i].begin()).second;
        ans[y] = c[i] + alt_sum;
        graph[i].erase({x, y});
        graph[x].erase({i, y});
        c[i] -= ans[y] / 2;
        c[x] -= ans[y] / 2;
        break;
    }

    compress();

    FOR(i, 1, m + 1) cout << ans[i] << '\n';
    return 0;
}