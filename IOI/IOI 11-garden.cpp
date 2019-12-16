#include "garden.h"
#include <bits/stdc++.h>
#include "gardenlib.h"

using namespace std;

typedef pair<int, int> pii;

const int MX = 200011;
vector<int> adj[MX * 2], g[MX * 2];

int F[MX * 2][2], c[2];

void connect(int u, int v, int N) {
    if (adj[u][0] == v || adj[u][0] == v - N) u = u + N;
    g[u].push_back(v);
}
void dfs(int u, int p, int it) {
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (v == p) {
            c[it] = F[u][it] + 1;
        } else if (F[v][it] == -1) {
            F[v][it] = F[u][it] + 1;
            dfs(g[u][i], p, it);
        }
    }
}
void count_routes(int N, int M, int P, int R[][2], int Q, int G[]) {
    memset(F, -1, sizeof F);
    for (int i = 0; i < M; ++i) {
        adj[R[i][0]].push_back(R[i][1]);
        adj[R[i][1]].push_back(R[i][0]);
    }
    for (int i = 0; i < N; ++i) {
        while (adj[i].size() > 2) adj[i].pop_back();
        connect(adj[i][0], i, N);
        if (adj[i].size() == 2) {
            connect(adj[i][1], i + N, N);
        } else {
            connect(adj[i][0], i + N, N);
        }
    }

    F[P][0] = 0;
    dfs(P, P, 0);
    F[P + N][1] = 0;
    dfs(P + N, P + N, 1);

    for (int k = 0; k < Q; k++) {
        int res = 0;
        for (int i = 0; i < N; ++i) {
            for (int it = 0; it < 2; it++) {
                if (F[i][it] == -1) continue;
                int rem = G[k];
                if (rem < F[i][it]) continue;
                rem -= F[i][it];
                if (rem == 0 || (c[it] && rem % c[it] == 0)) {
                    res++;
                    break;
                }
            }
        }
        answer(res);
    }
}
