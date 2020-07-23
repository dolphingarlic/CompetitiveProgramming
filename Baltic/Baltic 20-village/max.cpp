/*
Baltic 2020 Village (Maximum)
- The maximum distance is equal to sum(min(subtree[i], N - subtree[i]))
    - This is because we count how many people must go over each edge
- Find one of the centroids of the tree
- Then move the people skilfully (see the code for more details)
- Et voilà - you have AC
- Complexity: O(N log N) (from sorting)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll n;
vector<int> graph[100001], x_subtree, y_subtree;
ll max_dist = 0, subtree[100001], par[100001], x, y, ans[100001];
pair<ll, ll> centroid = {0, 0};

bool cmp(int A, int B) { return subtree[A] < subtree[B]; }

void dfs(int node = 1, int parent = 0) {
    par[node] = parent;
    subtree[node] = 1;
    for (int i : graph[node]) if (i != parent) {
        dfs(i, node);
        subtree[node] += subtree[i];
    }
    sort(graph[node].begin(), graph[node].end(), cmp);
    max_dist += 2 * min(subtree[node], n - subtree[node]);
    centroid = max(centroid, {min(subtree[node], n - subtree[node]), node});
}

void get_subtree(int node, int parent, vector<int> &vec) {
    vec.push_back(node);
    for (int i : graph[node]) if (i != parent)
        get_subtree(i, node, vec);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    FOR(i, 1, n) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs();
    x = centroid.second, y = par[x];
    if (subtree[x] * 2 > n) swap(x, y);
    get_subtree(x, y, x_subtree);
    get_subtree(y, x, y_subtree);

    FOR(i, 0, x_subtree.size()) {
        ans[x_subtree[i]] = y_subtree[i];
        ans[y_subtree[y_subtree.size() - x_subtree.size() + i]] = x_subtree[i];
    }
    FOR(i, 0, y_subtree.size() - x_subtree.size()) {
        ans[y_subtree[i]] = y_subtree[x_subtree.size() + i];
    }

    cout << max_dist << '\n';
    FOR(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
    return 0;
}