/*
POI 2005 Two Parties
- Firstly, it is always possible to split a graph into 2 subgraphs such that
  all nodes have even degree
    - We prove this by induction
    - Base case: N < 3 or all nodes have even degree
        - The trivial constructions for these cases work
    - Assume that we can split a graph with N-1 nodes and that our graph G has
      at least 1 node with odd degree
    - Let that node be V and the set of nodes connected to V be S
    - Ideally we'd like to join V with one of the two subgraphs made from G\{V}
        - However, notice that if we can't just straight-up split G\{V} and join V
          since this would result in odd degrees
    - Instead, invert all the edges in the subgraph with nodes from S
        - Since there are an odd number of elements in S, the parity of each node's
          degree in G\{V} is conserved
        - Now we can just split this new graph into 2 components and add V to the
          component with an even number of elements in S
    - This way we can construct the partitions (using recursion)
- Complexity: O(N^3)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n;
bool graph[201][201];

vector<int> split(vector<int> nodes) {
    if (nodes.size() < 3) return {nodes[0]};

    for (int i : nodes) {
        int deg = 0;
        FOR(x, 1, n + 1) deg += graph[i][x];

        if (deg & 1) {
            vector<int> new_nodes;
            for (int x : nodes) if (x != i) new_nodes.push_back(x);

            vector<int> conn;
            FOR(x, 1, n + 1) if (graph[i][x]) conn.push_back(x);
            FOR(x, 0, deg) {
                FOR(y, x + 1, deg) {
                    graph[conn[x]][conn[y]] = !graph[conn[x]][conn[y]];
                    graph[conn[y]][conn[x]] = !graph[conn[y]][conn[x]];
                }
                graph[conn[x]][i] = false;
            }

            vector<int> s = split(new_nodes);

            int cnt = 0;
            for (int x : s) cnt += graph[i][x];
            if (!(cnt & 1)) s.push_back(i);

            return s;
        }
    }

    return nodes;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    vector<int> s;
    cin >> n;
    FOR(i, 1, n + 1) {
        int m;
        cin >> m;
        FOR(j, 0, m) {
            int x;
            cin >> x;
            graph[i][x] = true;
        }
        s.push_back(i);
    }

    vector<int> part = split(s);
    cout << part.size() << '\n';
    for (int i : part) cout << i << ' ';
    return 0;
}