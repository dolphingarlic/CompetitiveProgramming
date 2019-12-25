/*
IOI 2007 Training
- Firstly, the limit on the maximum degree implies bitmasking
- Secondly, we are given a tree so we would probably want to do a tree dp
- Split the non-tree edges into 2 categories:
    - Even if the distance between the 2 endpoints is even (these form even cycles)
    - Odd if the distance is odd (these form odd cycles)
- Clearly, we would need to block all odd edges
- An even cycle is formed from the even edges iff they "overlap"
- This means that each tree edge can be part of at most 1 odd cycle
- dp[i][mask] = The maximum sum of non-tree edges we keep in the subtree of i when
                the children specified in mask aren't considered
              = max(
                  sum_of_children(dp[child][0]),
                  max(Edge cost + sum_of_decomposed_paths_from_edge)
                )
- We can find this with LCA and bitmasking
- LCA can be naive because of low constraints
- Complexity: O(M log M + MN + M * 2^max_deg)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Road {
    int a, b, c, lca;
};

vector<int> tree[5001];
vector<Road> roads;
pair<int, int> par[5001];
bool even_to_root[5001];
int dp[5001][1 << 10], timer = 0, tin[5001], tout[5001], deg[5001];

bool operator<(Road A, Road B) {
    return tout[A.lca] < tout[B.lca];
}

void get_ancestors(int node = 1, int parent = 0) {
    even_to_root[node] = !even_to_root[parent];
    tin[node] = ++timer;
    for (int i : tree[node]) {
        if (i != parent) {
            par[i] = {node, 1 << deg[node]++};
            get_ancestors(i, node);
        }
    }
    tout[node] = ++timer;
}

bool is_parent(int A, int B) {
    return tin[A] <= tin[B] && tout[A] >= tout[B];
}
int lca(int A, int B) {
    while (!is_parent(A, B)) A = par[A].first;
    return A;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, cost = 0;
    cin >> n >> m;
    FOR(i, 0, m) {
        int a, b, c;
        cin >> a >> b >> c;
        cost += c;
        if (!c) {
            tree[a].push_back(b);
            tree[b].push_back(a);
        }

        roads.push_back({a, b, c});
    }

    get_ancestors();

    FOR(i, 0, m) roads[i].lca = lca(roads[i].a, roads[i].b);
    sort(roads.begin(), roads.end());

    for (Road i : roads) {
        if (i.c && even_to_root[i.a] ^ even_to_root[i.b]) continue;

        int sm = i.c;
        pair<int, int> A, B;
        for (A = {i.a, 0}; A.first != i.lca; A = par[A.first]) sm += dp[A.first][A.second];
        for (B = {i.b, 0}; B.first != i.lca; B = par[B.first]) sm += dp[B.first][B.second];

        for (int mask = (1 << deg[i.lca]) - 1; ~mask; mask--) {
            if (!(mask & A.second || mask & B.second)) {
                dp[i.lca][mask] = max(dp[i.lca][mask], sm + dp[i.lca][mask | A.second | B.second]);
            }
        }
    }

    cout << cost - dp[1][0];
    return 0;
}