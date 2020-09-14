/*
Balkan 2016 Acrobat
- We want to transform the graph into one with an Eulerian circuit
- First, we make the degrees of all nodes on side A even
- Notice how if we reverse an edge (a[i], b[i]), then the parity
  of nodes a[i] and b[i] toggle
    - This means we can just do a DFS and greedily toggle the parities
- Next, we want to make the graph connected
    - This is a simple application of DSU
- Finally, we need to get rid of all odd-degree nodes on side B
    - Just find those nodes and pair them up
- Complexity: O(N + M), at most 5N/2 changes
*/

#include <bits/stdc++.h>
using namespace std;

int a[300001], b[300001], cmp[600001];
bool cnt[300001], visited[300001];
vector<pair<int, int>> graph[300001];
vector<array<int, 3>> ans;

int find(int A) {
    while (A != cmp[A]) A = cmp[A], cmp[A] = cmp[cmp[A]];
    return A;
}

void onion(int A, int B) { cmp[find(A)] = find(B); }

bool dfs(int node) {
    visited[node] = true;
    for (pair<int, int> i : graph[node]) {
        if (!visited[i.first] && dfs(i.first)) {
            ans.push_back({1, a[i.second], b[i.second]});
            swap(a[i.second], b[i.second]);
            cnt[node] ^= 1;
        }
    }
    return cnt[node];
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        cnt[a[i]] ^= 1;
        graph[a[i]].push_back({b[i], i});
        graph[b[i]].push_back({a[i], i});
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && dfs(i)) return cout << -1, 0;
    }

    memset(cnt, 0, sizeof cnt);
    iota(cmp + 1, cmp + 2 * n + 1, 1);
    for (int i = 0; i < m; i++) {
        cnt[b[i]] ^= 1;
        onion(a[i] + n, b[i]);
    }
    for (int i = 1; i <= n; i++) if (find(1) != find(i)) {
        ans.push_back({2, 1, i});
        cnt[1] ^= 1;
        cnt[i] ^= 1;
        onion(1, i);
    }
    vector<int> odd;
    for (int i = 1; i <= n; i++) if (cnt[i]) odd.push_back(i);
    for (int i = 0; i < odd.size(); i += 2) ans.push_back({2, odd[i], odd[i + 1]});

    cout << ans.size() << '\n';
    for (array<int, 3> i : ans) {
        cout << i[0] << ' ' << i[1] << ' ' << i[2] << '\n';
    }
    return 0;
}