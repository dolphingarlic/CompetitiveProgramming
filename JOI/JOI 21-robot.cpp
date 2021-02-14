/*
JOI 2021 Robot
- Lemma: We can always recolour an edge (u, v) so that its colour is different
         from those of the other edges incident to u and v
    - One can prove this using the PHP
- If we want to traverse an edge with colour c, we either recolour that edge or all
  other incident edges with the same colour
- Let dp[i] = The minimum cost for the robot to get to node i
- Let dp2[i][c] = The minimum cost for the robot to get to node i if it previously
                  used a node of colour c to get to i which should have been recoloured
                  but hasn't been recoloured yet, since we'll also traverse another
                  edge of colour c from node i and recolour all edges besides that
- The rest is just Dijkstra's algorithm + some casework
- Complexity: O((N + M) log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 1e18;

struct Edge {
    int to, c;
    ll p;
};

map<int, vector<Edge>> graph[100001];
ll dp[100001];
map<int, ll> dp2[100001], psum[100001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        ll p;
        cin >> u >> v >> c >> p;
        graph[u][c].push_back({v, c, p});
        graph[v][c].push_back({u, c, p});
        psum[u][c] += p;
        psum[v][c] += p;
    }

    memset(dp, 0x3f, sizeof dp);
    dp[1] = 0;
    priority_queue<tuple<ll, int, int>> pq;
    pq.push({0, 1, 0});
    while (pq.size()) {
        ll cost;
        int node, c;
        tie(cost, node, c) = pq.top();
        pq.pop();

        if (c) {
            if (dp2[node][c] != -cost) continue;
            for (Edge i : graph[node][c]) {
                // We can't flip i in this case
                ll case1 = psum[node][c] - i.p;
                if (case1 - cost < dp[i.to]) {
                    dp[i.to] = case1 - cost;
                    pq.push({-dp[i.to], i.to, 0});
                }
            }
        } else {
            if (dp[node] != -cost) continue;
            for (auto& i : graph[node]) {
                for (Edge j : i.second) {
                    // Case 1: We don't flip j
                    ll case1 = psum[node][j.c] - j.p - cost;
                    if (case1 < dp[j.to]) {
                        dp[j.to] = case1;
                        pq.push({-dp[j.to], j.to, 0});
                    }
                    // Case 2: We flip j but not another edge of the same colour
                    ll case2 = j.p - cost;
                    if (case2 < dp[j.to]) {
                        dp[j.to] = case2;
                        pq.push({-dp[j.to], j.to, 0});
                    }
                    // Case 3: We flip j and another edge of the same colour
                    ll case3 = -cost;
                    if (!dp2[j.to].count(j.c) || case3 < dp2[j.to][j.c]) {
                        dp2[j.to][j.c] = case3;
                        pq.push({-dp2[j.to][j.c], j.to, j.c});
                    }
                }
            }
        }
    }
    cout << (dp[n] > INF ? -1 : dp[n]);
    return 0;
}