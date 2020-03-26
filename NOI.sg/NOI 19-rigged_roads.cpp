#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

pair<int, int> edges[300001];
bool rigged[300001];

int val[300001], tin[300001]{INT_MIN}, tout[300001]{INT_MAX}, timer = 1;
pair<int, int> parent[300001];
vector<pair<int, int>> mst[300001];

inline bool is_ancestor(int a, int b) {
    return (tin[a] <= tin[b] && tout[a] >= tout[b]);
}

void dfs(int node) {
    tin[node] = timer++;
    for (pair<int, int> i : mst[node]) {
        if (!tin[i.first]) {
            parent[i.first] = {node, i.second};
            dfs(i.first);
        }
    }
    tout[node] = timer++;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, m + 1) { cin >> edges[i].first >> edges[i].second; }
    FOR(i, 1, n) {
        int r;
        cin >> r;
        rigged[r] = true;
    }
    FOR(i, 1, m + 1) {
        if (rigged[i]) {
            mst[edges[i].first].push_back({edges[i].second, i});
            mst[edges[i].second].push_back({edges[i].first, i});
        }
    }
    dfs(1);

    int cnt = 1;
    FOR(i, 1, m + 1) {
        // We also have to merge paths together
        int a = edges[i].first, b = edges[i].second;
        set<int> to_process;
        while (!is_ancestor(parent[a].first, b)) {
            to_process.insert(parent[a].second);
            int temp = parent[a].first;
            parent[a] = parent[temp];
            a = temp;
        }
        if (!is_ancestor(a, b)) to_process.insert(parent[a].second);
        while (!is_ancestor(parent[b].first, a)) {
            to_process.insert(parent[b].second);
            int temp = parent[b].first;
            parent[b] = parent[temp];
            b = temp;
        }
        if (!is_ancestor(b, a)) to_process.insert(parent[b].second);

        for (int j : to_process) if (!val[j]) val[j] = cnt++;
        if (!val[i]) val[i] = cnt++;
    }

    FOR(i, 1, m + 1) cout << val[i] << ' ';
    return 0;
}