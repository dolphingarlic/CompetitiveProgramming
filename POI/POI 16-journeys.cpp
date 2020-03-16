/*
POI 2016 Amusing Journeys
- Firstly, notice that all cycles are contained within biconnected components (BCCs)
- Split the graph into its BCCs
- For each BCC, notice that it is amusing iff it is either a single cycle or an onion
  (i.e. a graph where exactly 2 nodes have degree > 2 and all paths going between them are of equal length)
- Convince yourself that this is true
- Now just make sure each BCC has the same cycle length. Let this length be L
- If the BCC is a cycle, it contributes 2L amusing journeys
- If the BCC is an onion, it contributes 2L * (kC2) where k is the number of paths between the 2 "endpoints" of the onion
- Complexity: O(N + M)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

vector<int> graph[500001], bcc_graph[500001];
vector<pair<int, int>> bcc_edges;
int low[500001], tin[500001], timer = 1;
ll dist[500001], deg[500001];
stack<pair<int, int>> stck;

ll cycles = 0, len = 0;

void reset() {
    for (pair<int, int> i : bcc_edges) {
        bcc_graph[i.first].clear();
        bcc_graph[i.second].clear();
        deg[i.first] = deg[i.second] = 0;
        dist[i.first] = dist[i.second] = 0;
    }
    bcc_edges.clear();
}

bool bfs(int src, int dest) {
    queue<int> q;
    q.push(src);
    dist[src] = 1;
    while (q.size()) {
        int curr = q.front();
        q.pop();
        for (int i : bcc_graph[curr]) {
            if (i == dest) {
                if (!dist[i]) dist[i] = dist[curr] + 1;
                if (dist[curr] + 1 != dist[i]) return false;
            } else if (!dist[i]) {
                dist[i] = dist[curr] + 1;
                q.push(i);
            }
        }
    }
    return true;
}

bool check() {
    if (bcc_edges.size() == 1) return true;

    vector<int> onion_endpoints;
    for (pair<int, int> i : bcc_edges) {
        bcc_graph[i.first].push_back(i.second);
        bcc_graph[i.second].push_back(i.first);

        deg[i.first]++; deg[i.second]++;
        if (deg[i.first] == 3) onion_endpoints.push_back(i.first);
        if (deg[i.second] == 3) onion_endpoints.push_back(i.second);
    }
    
    if (!onion_endpoints.size()) {
        if (!len) len = bcc_edges.size();
        if (len != bcc_edges.size()) return false;
        cycles = (cycles + 1) % MOD;
        return true;
    }
    if (onion_endpoints.size() != 2) return false;

    int x = onion_endpoints[0], y = onion_endpoints[1];
    if (!bfs(x, y)) return false;
    if (!len) len = 2 * (dist[y] - 1);
    if (len != 2 * (dist[y] - 1)) return false;
    cycles = (cycles + deg[x] * (deg[x] - 1) / 2) % MOD;
    return true;
}

bool dfs(int node = 1, int parent = 0) {
    low[node] = tin[node] = timer++;

    for (int i : graph[node]) if (i != parent) {
        if (tin[i]) {
            if (tin[i] < tin[node]) {
                stck.push({node, i});
                low[node] = min(low[node], tin[i]);
            }
        } else {
            stck.push({node, i});
            if (!dfs(i, node)) return false;
            low[node] = min(low[node], low[i]);

            if (low[i] >= tin[node]) {
                pair<int, int> lst;
                do {
                    lst = stck.top();
                    bcc_edges.push_back(lst);
                    stck.pop();
                } while (lst != make_pair(i, node) && lst != make_pair(node, i));

                if (!check()) return false;
                reset();
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, m) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    if (m == n - 1) cout << "BRAK";
    else if (dfs()) cout << "TAK\n" << len << ' ' << (cycles * 2 * len) % MOD;
    else cout << "NIE";
    return 0;
}