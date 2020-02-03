#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int has_end[2020202], to[2020202], pref[2020202];
pair<int, int> teleporters[2020202];

int cnt = 0, sizes[2020202];
bool visited[2020202];

void dfs(int node, int cycle) {
    visited[node] = true;
    sizes[cycle]++;
    if (!visited[to[node]]) dfs(to[node], cycle);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, n) {
        int a, b;
        cin >> a >> b;
        has_end[a] = has_end[b] = 1;
        teleporters[i] = {a, b};
    }
    FOR(i, 1, 2020202) pref[i] = pref[i - 1] + has_end[i];
    FOR(i, 0, n) {
        to[pref[teleporters[i].first] - 1] = pref[teleporters[i].second];
        to[pref[teleporters[i].second] - 1] = pref[teleporters[i].first];
    }

    FOR(i, 0, 2 * n) if (!visited[i]) dfs(i, cnt++);
    sort(sizes + 1, sizes + cnt, greater<int>());
    for (int i = 1; i < cnt && m; i++, m--) sizes[0] += sizes[i] + 2;
    sizes[0] += (m / 2) * 4 + (m & 1);

    cout << sizes[0] - 1;
    return 0;
}