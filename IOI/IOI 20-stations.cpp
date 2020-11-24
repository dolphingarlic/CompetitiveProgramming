/*
IOI 2020 Stations
- Just alternate between tin and tout
- Complexity: O(N) with max_label == N - 1
*/

#include "stations.h"
#include <vector>
#include <algorithm>

std::vector<int> graph[1000];
int tin[1000], tout[1000], timer;

void dfs(int node = 0, int parent = -1) {
    tin[node] = timer++;
    for (int i : graph[node]) if (i != parent) dfs(i, node);
    tout[node] = timer++;
}

std::vector<int> label(int n, int k, std::vector<int> u, std::vector<int> v) {
    for (int i = 0; i < n; i++) graph[i].clear();
    for (int i = 0; i < n - 1; i++) {
        graph[u[i]].push_back(v[i]);
        graph[v[i]].push_back(u[i]);
    }
    timer = 0;
    dfs();
    std::vector<int> labels(n);
    for (int i = 0; i < n; i++) {
        labels[i] = tin[i] * (tin[i] - 1 & 1) + tout[i] * (tout[i] - 1 & 1) >> 1;
    }
    return labels;
}

int find_next_station(int s, int t, std::vector<int> c) {
    if (s < c.back()) {
        if (t < s || t > c.back()) return c.back();
        return *std::lower_bound(c.begin(), c.end(), t);
    } else {
        if (t > s || t < c[0]) return c[0];
        return *prev(std::upper_bound(c.begin(), c.end(), t));
    }
}
