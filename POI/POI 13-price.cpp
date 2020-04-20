/*
POI 2013 Price
- Just do Dijkstra but search 2 edges deep
    - This is O(M^2) if we just do this naively though
    - Notice how if we encounter A->B->C in Dijkstra, then we never use X->B->C for
      a shorter route to C, since the cost is constant
        - This means we can just erase edge B->C after we use it 
    - We have to be careful to skip triangles though
        - Notice how there are O(M sqrt(M)) triangles, so we're fine just naively checking
- Complexity: O(N log N + M sqrt(M))
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

set<int> graph[100001], second_visit[100001];
int visited[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k, a, b;
    cin >> n >> m >> k >> a >> b;
    FOR(i, 0, m) {
        int u, v;
        cin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);
        second_visit[u].insert(v);
        second_visit[v].insert(u);
    }

    priority_queue<pair<int, int>> pq;
    pq.push({-1, k});
    while (pq.size()) {
        pair<int, int> curr = pq.top();
        pq.pop();
        if (!visited[curr.second]) {
            visited[curr.second] = -curr.first;
            for (int i : graph[curr.second]) {
                pq.push({curr.first - a, i});

                vector<int> to_remove;
                for (int j : second_visit[i]) {
                    if (graph[curr.second].find(j) == graph[curr.second].end()) {
                        to_remove.push_back(j);
                        pq.push({curr.first - b, j});
                    }
                }
                for (int j : to_remove) second_visit[i].erase(j);
            }
        }
    }

    FOR(i, 1, n + 1) cout << visited[i] - 1 << '\n';
    return 0;
}