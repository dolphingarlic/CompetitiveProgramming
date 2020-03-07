#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

#define MAX 100001
#define NIL 0
#define INF (1 << 28)

vector<int> G[MAX];
int n, m, match[MAX], dist[MAX];
// n: number of nodes on left side, nodes are numbered 1 to n
// m: number of nodes on right side, nodes are numbered n+1 to n+m
// G = NIL[0] ∪ G1[G[1---n]] ∪ G2[G[n+1---n+m]]

bool bfs() {
    int i, u, v, len;
    queue<int> Q;
    for (i = 1; i <= n; i++) {
        if (match[i] == NIL) {
            dist[i] = 0;
            Q.push(i);
        } else
            dist[i] = INF;
    }
    dist[NIL] = INF;
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        if (u != NIL) {
            len = G[u].size();
            for (i = 0; i < len; i++) {
                v = G[u][i];
                if (dist[match[v]] == INF) {
                    dist[match[v]] = dist[u] + 1;
                    Q.push(match[v]);
                }
            }
        }
    }
    return (dist[NIL] != INF);
}

bool dfs(int u) {
    int i, v, len;
    if (u != NIL) {
        len = G[u].size();
        for (i = 0; i < len; i++) {
            v = G[u][i];
            if (dist[match[v]] == dist[u] + 1) {
                if (dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    if (__builtin_popcount(n) == 1) {
        FOR(i, m, n + m) cout << (i & (n - 1)) << ' ' << i << '\n';
    } else {
        FOR(i, 0, n) FOR(j, m, m + n) if ((j & i) == i) G[i].push_back(j);
        while (bfs()) FOR(i, 0, n) if (match[i] == NIL && dfs(i)) cout << i << ' ' << match[i] << '\n';
    }
    return 0;
}