#include "grader.h"
#include "encoder.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

vector<int> graph[1000];
int par[1000], dist[1000][36], state[1000];
bool visited[1000];

void dfs(int node = 0, int parent = 0) {
    par[node] = parent;
    visited[node] = true;
    for (int i : graph[node]) if (!visited[i]) dfs(i, node);
}

void encode(int nv, int nh, int ne, int *v1, int *v2) {
    FOR(i, 0, ne) {
        graph[v1[i]].push_back(v2[i]);
        graph[v2[i]].push_back(v1[i]);
    }
    dfs();
    FOR(i, 0, nv) FOR(j, 0, 10) encode_bit((par[i] & (1 << j)) >> j);

    FOR(hub, 0, nh) {
        dist[hub][hub] = 1;
        queue<int> q;
        q.push(hub);
        while (q.size()) {
            int curr = q.front();
            q.pop();
            for (int i : graph[curr]) if (!dist[i][hub]) {
                dist[i][hub] = dist[curr][hub] + 1;
                q.push(i);
            }
        }

        FOR(i, 0, nv) {
            if (dist[i][hub] == dist[par[i]][hub]) state[i] = 0;
            else if (dist[i][hub] > dist[par[i]][hub]) state[i] = 1;
            else state[i] = 2;
        }
        for (int i = 0; i < nv; i += 5) {
            int enc = 0;
            FOR(j, i, min(i + 5, nv)) enc = (enc * 3 + state[j]);
            FOR(j, 0, 8) encode_bit((enc & (1 << j)) >> j);
        }
    }
}
