/*
COI 2007 Tamnica
- We can compress the graph since we only care about nodes given to us
- Find which rooms are connected to which using maths
- Then just run Dijkstra to get the shortest distance from 1 to N
- Complexity: O(K log K)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    int k;
    cin >> n >> k;
    vector<ll> nodes = {1, n};
    unordered_map<ll, vector<pair<ll, ll>>> graph;
    while (k--) {
        ll b;
        cin >> b;
        nodes.push_back(b);

        ll cont = ll(sqrt(b));
        if (cont * cont < b) cont++;

        if (cont * (cont - 1) + 1 < b) {
            nodes.push_back(b - 4 * cont + 5);
            graph[b - 4 * cont + 5].push_back({b, 1});
        } else if (cont * (cont - 2) + 2 < b) {
            nodes.push_back(b - 4 * cont + 7);
            graph[b - 4 * cont + 7].push_back({b, 1});
        } else if (cont * (cont - 3) + 3 < b) {
            nodes.push_back(b - 4 * cont + 9);
            graph[b - 4 * cont + 9].push_back({b, 1});
        } else {
            nodes.push_back(b - 4 * cont + 11);
            graph[b - 4 * cont + 11].push_back({b, 1});
        }
    }

    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
    FOR(i, 1, nodes.size()) {
        graph[nodes[i]].push_back({nodes[i - 1], nodes[i] - nodes[i - 1]});
        graph[nodes[i - 1]].push_back({nodes[i], nodes[i] - nodes[i - 1]});
    }

    priority_queue<pair<ll, ll>> pq;
    unordered_set<ll> visited;
    pq.push({0, 1});
    while (pq.size()) {
        pair<ll, ll> curr = pq.top();
        pq.pop();
        if (curr.second == n) return cout << -curr.first, 0;
        if (visited.find(curr.second) == visited.end()) {
            visited.insert(curr.second);
            for (pair<ll, ll> i : graph[curr.second]) {
                if (visited.find(i.first) == visited.end()) {
                    pq.push({curr.first - i.second, i.first});
                }
            }
        }
    }
    return 0;
}