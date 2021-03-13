/*
COCI 2021 Alias
- Map each word to an integer, and do Dijkstra's
- Complexity: O(QN log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

map<string, int> mp;
vector<pair<int, ll>> graph[1000];
ll visited[1000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, cnt = 0;
    cin >> n >> m;
    while (m--) {
        string s, t;
        ll v;
        cin >> s >> t >> v;
        if (!mp.count(s)) mp[s] = cnt++;
        if (!mp.count(t)) mp[t] = cnt++;
        graph[mp[s]].push_back({mp[t], v});
    }
    int q;
    cin >> q;
    while (q--) {
        string s, t;
        cin >> s >> t;
        int src = mp[s], dest = mp[t];
        memset(visited, 0x3f, sizeof visited);
        priority_queue<pair<ll, int>> pq;
        visited[src] = 0;
        pq.push({0, src});
        bool found = false;
        while (pq.size()) {
            ll cost;
            int node;
            tie(cost, node) = pq.top();
            pq.pop();
            if (-cost != visited[node]) continue;
            if (node == dest) {
                found = true;
                cout << -cost << '\n';
                break;
            }
            for (pair<int, ll> i : graph[node]) if (i.second - cost < visited[i.first]) {
                visited[i.first] = i.second - cost;
                pq.push({cost - i.second, i.first});
            }
        }
        if (!found) cout << "Roger\n";
    }
    return 0;
}