#include "grader.h"
#include "decoder.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[1000];
int par[1000], dist[1000][36], state[1000];

void dfs(int hub, int node = 0, int parent = 0) {
    dist[node][hub] = dist[par[node]][hub] + (state[node] + 1) % 3 - 1;
    for (int i : graph[node]) if (i != parent) dfs(hub, i, node);
}

void decode(int nv, int nh) {
    FOR(i, 0, nv) {
        FOR(j, 0, 10) par[i] += decode_bit() << j;
        graph[par[i]].push_back(i);
    }

    FOR(hub, 0, nh) {
        for (int i = 0; i < nv; i += 5) {
            int enc = 0;
            FOR(j, 0, 8) enc += decode_bit() << j;
            for (int j = min(i + 5, nv) - 1; j >= i; j--) {
                state[j] = enc % 3;
                enc /= 3;
            }
        }

        int curr = hub;
        while (curr != par[curr]) {
            dist[par[curr]][hub] = dist[curr][hub] - (state[curr] + 1) % 3 + 1;
            curr = par[curr];
        }
        dfs(hub);

        FOR(i, 0, nv) hops(hub, i, dist[i][hub]);
    }
}
