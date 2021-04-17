/*
COI 2017 Zagrade
- Centroid decomposition (see IOI 2011 Race)
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int fwd[300001], rev[300001], subtree[300001];
vector<int> graph[300001];
ll ans = 0;
bool processed[300001];

int get_subtree_sizes(int node, int parent = 0) {
    subtree[node] = 1;
    for (int i : graph[node])
        if (i != parent && !processed[i])
            subtree[node] += get_subtree_sizes(i, node);
    return subtree[node];
}

int get_centroid(int node, int target, int parent = 0) {
    for (int i : graph[node])
        if (i != parent && !processed[i] && subtree[i] > target)
            return get_centroid(i, target, node);
    return node;
}

void calc(int node, int parent, int *v, vector<int> &cnt, int curr, int mn) {
    curr += v[node];
    mn = min(0, mn + v[node]);

    if (mn == 0) ans += cnt[curr];
    for (int i : graph[node])
        if (i != parent && !processed[i]) calc(i, node, v, cnt, curr, mn);
}

void upd(int node, int parent, int *v, vector<int> &cnt, int curr, int mn) {
    curr += v[node];
    mn = min(0, mn + v[node]);

    if (mn == 0) cnt[curr]++;
    for (int i : graph[node])
        if (i != parent && !processed[i]) upd(i, node, v, cnt, curr, mn);
}

void decompose(int node = 1) {
    int sz = get_subtree_sizes(node);
    int centroid = get_centroid(node, sz / 2);

    vector<int> cnt_fwd(sz + 1), cnt_rev(sz + 1);
    if (fwd[centroid] == 1)
        cnt_fwd[1]++;
    else
        cnt_rev[1]++;
    for (int i : graph[centroid])
        if (!processed[i]) {
            calc(i, centroid, fwd, cnt_rev, 0, 0);
            calc(i, centroid, rev, cnt_fwd, 0, 0);
            upd(i, centroid, fwd, cnt_fwd, fwd[centroid],
                min(0, fwd[centroid]));
            upd(i, centroid, rev, cnt_rev, rev[centroid],
                min(0, rev[centroid]));
        }

    processed[centroid] = true;
    for (int i : graph[centroid])
        if (!processed[i]) decompose(i);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        if (c == '(')
            fwd[i] = 1, rev[i] = -1;
        else
            fwd[i] = -1, rev[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    decompose();
    cout << ans;
    return 0;
}
