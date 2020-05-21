/*
IOI 2008 Islands
- to, split the graph up into its connected components. We want the sum of the longest
  paths in each component
- Notice how each component is made of a single cycle with trees appended to each node on the cycle
- Case 1: The longest path lies in one of the trees
    - Just use DP to find this length
- Case 2: The longest path goes from one tree to the other and crosses the cycle
    - Let dp[i] = The length of the longest path going through node i
    - If we flatten the cycle by removing an edge, then notice how
      we can use prefix sums to get the answer in this case
- Just handle these 2 cases for each component
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Edge {
    int idx, to, len;
    bool operator!=(Edge B) { return idx != B.idx; }
};

vector<Edge> graph[1000001], cycle;
ll cmp_ans, p[3][1000001];
int cycle_start = 0, discarded;
bool visited[1000001], adding = false;

void find_cycle(int node, Edge parent = {0, 0, 0}) {
    if (visited[node]) {
        cycle_start = node;
        cycle.push_back({0, node, 0});
        cycle.push_back(parent);
        adding = true;
        return;
    }
    visited[node] = true;
    for (Edge i : graph[node]) if (i != parent) {
        find_cycle(i.to, {i.idx, node, i.len});
        if (cycle_start) {
            if (node == cycle_start) adding = false;
            if (adding) cycle.push_back(parent);
            else visited[parent.to] = false;
            return;
        }
    }
    visited[node] = false;
}

void calc_tree(int node, int parent = 0) {
    visited[node] = true;
    ll mx = 0, sc = 0;
    for (Edge i : graph[node]) if (!visited[i.to]) {
        calc_tree(i.to, node);
        if (p[2][i.to] + i.len > mx) sc = mx, mx = p[2][i.to] + i.len;
        else if (p[2][i.to] + i.len > sc) sc = p[2][i.to] + i.len;
    }
    p[2][node] = mx;
    cmp_ans = max(cmp_ans, mx + sc);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        int v, l;
        cin >> v >> l;
        graph[i].push_back({i, v, l});
        graph[v].push_back({i, i, l});
    }

    ll ans = 0;
    FOR(i, 1, n + 1) if (!visited[i]) {
        cycle.clear();
        cycle_start = 0;
        find_cycle(i);
        discarded = cycle.back().len;
        cycle.pop_back();

        cmp_ans = 0;

        FOR(j, 1, cycle.size()) p[0][cycle[j].to] = p[0][cycle[j - 1].to] + cycle[j].len;
        for (int j = cycle.size() - 2; ~j; j--)
            p[1][cycle[j].to] = p[1][cycle[j + 1].to] + cycle[j + 1].len;

        ll mx = 0;
        FOR(j, 0, cycle.size()) {
            calc_tree(cycle[j].to);

            cmp_ans = max(cmp_ans, p[2][cycle[j].to] + p[0][cycle[j].to] + mx);
            mx = max(mx, p[2][cycle[j].to] - p[0][cycle[j].to]);
        }

        mx = p[2][cycle.back().to] + p[1][cycle.back().to];
        for (int j = cycle.size() - 2; ~j; j--) {
            cmp_ans = max(cmp_ans, p[2][cycle[j].to] + p[0][cycle[j].to] + mx + discarded);
            mx = max(mx, p[2][cycle[j].to] + p[1][cycle[j].to]);
        }

        ans += cmp_ans;
    }
    cout << ans;
    return 0;
}