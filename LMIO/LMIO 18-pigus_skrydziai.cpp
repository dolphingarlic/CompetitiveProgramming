/*
LMIO 2018 Pigus Skrydziai
- We either take all edges incident to one node or we take a triangle
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll prof[300001];
vector<pair<ll, int>> graph[300001];
map<pair<int, int>, ll> edges;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    while (m--) {
        int a, b;
        ll v;
        cin >> a >> b >> v;
        prof[a] += v, prof[b] += v;
        graph[a].push_back({v, b});
        graph[b].push_back({v, a});
        edges[{a, b}] = edges[{b, a}] = v;
    }
    ll ans = *max_element(prof + 1, prof + n + 1);
    FOR(i, 1, n + 1) {
        sort(graph[i].begin(), graph[i].end(), greater<pair<ll, int>>());
        if (graph[i].size() > 1) {
            ans = max(ans, graph[i][0].first + graph[i][1].first +
                               edges[{graph[i][0].second, graph[i][1].second}]);
        }
    }
    cout << ans;
    return 0;
}