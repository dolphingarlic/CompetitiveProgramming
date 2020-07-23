/*
Baltic 2020 Graph
- N.B. The graph isn't necessarily connected, so apply the following on all connected components
- Let node 1 have value X
- Then do a DFS
- We know the value of each node in terms of X from the previously visited node and edge
- This means we get a bunch of linear equations (mx + c) for each node
- If there is more than 1 linear equation for any node, we can either find X or show that a labelling
  is not possible
- If all nodes only have 1 linear equation though, then we must find X to minimize the sum of their
  absolute values
    - Notice how we can simply sort by (-m * c) and take the median in this case, since abs(m) = 1
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

pair<ll, ll> labels[100001];
vector<pair<ll, ll>> graph[100001];
ll twice_x, ans[100001];
vector<ll> processed;
bool know_x = false, visited[100001];

bool incompatible(pair<ll, ll> A, pair<ll, ll> B) {
    if (know_x)
        return (A.first * twice_x + 2 * A.second !=
                B.first * twice_x + 2 * B.second);
    return (A.first == B.first && A.second != B.second);
}

void calc_x(pair<ll, ll> A, pair<ll, ll> B) {
    if (A.first == -1) swap(A, B);
    twice_x = B.second - A.second;
    know_x = true;
}

void dfs(ll node = 1) {
    visited[node] = true;
    processed.push_back(node);
    for (pair<ll, ll> i : graph[node]) {
        pair<ll, ll> assign = {-labels[node].first,
                               i.second - labels[node].second};
        if (!visited[i.first]) {
            labels[i.first] = assign;
            dfs(i.first);
        } else {
            if (labels[i.first] == assign) continue;
            if (incompatible(labels[i.first], assign)) {
                cout << "NO\n";
                exit(0);
            }
            calc_x(labels[i.first], assign);
        }
    }
}

void assign_opt_x() {
    vector<int> salient_points;
    for (int i : processed)
        salient_points.push_back(-labels[i].first * labels[i].second);
    sort(salient_points.begin(), salient_points.end());
    twice_x = 2 * salient_points[salient_points.size() / 2];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, m;
    cin >> n >> m;
    while (m--) {
        ll u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    FOR(i, 1, n + 1) {
        if (!visited[i]) {
            processed.clear();
            know_x = false;
            labels[i] = {1, 0};
            dfs(i);
            if (!know_x) assign_opt_x();
            for (int i : processed)
                ans[i] = labels[i].first * twice_x + 2 * labels[i].second;
        }
    }

    cout << "YES\n";
    FOR(i, 1, n + 1) cout << ans[i] / 2.0 << " \n"[i == n];
    return 0;
}