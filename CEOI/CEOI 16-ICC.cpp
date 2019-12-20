/*
CEOI 2016 ICC
- We want to binary search for the answer somehow
- We should always group cities in the same component together or else
  query always returns 1
- Consider the binary representations of the components
- If we split the components based on their i-th bit (from the right), then
  query(Split from i-th bit) == 1 for the first time iff all bits to the right of
  i are the same for the 2 newly connected components
- We can fill in the rest of the bits by fixing a particular bit and seeing if the
  query still returns 1
- After finding the 2 connected components, we can just binary search within those components
*/

#include "icc.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

vector<int> a, b, cmp[101], graph[101];
bool visited[101];

void dfs(int node, int idx) {
    visited[node] = true;
    cmp[idx].push_back(node);
    for (int i : graph[node]) if (!visited[i]) dfs(i, idx);
}

void run (int n) {
    while (true) {
        int idx = 0;
        for (int i = 1; i <= n; i++)
            if (!visited[i]) dfs(i, idx++);

        for (int i = 0; ; i++) {
            // Check if the current split has a path between stuff
            a.clear(); b.clear();
            FOR(j, 0, idx) {
                for (int k : cmp[j]) {
                    if ((j >> i) & 1) a.push_back(k);
                    else b.push_back(k);
                }
            }

            if (!query(a.size(), b.size(), a.data(), b.data())) continue;

            // Find the exact bits
            int exact = 0;
            FOR(k, 0, i) {
                a.clear(); b.clear();
                FOR(j, 0, idx) {
                    if ((j & ((1 << (k + 1)) - 1)) == exact) {
                        for (int l : cmp[j]) {
                            if ((j >> i) & 1) a.push_back(l);
                            else b.push_back(l);
                        }
                    }
                }

                if (!query(a.size(), b.size(), a.data(), b.data())) exact |= (1 << k);
            }

            // Binary search in the component
            a.clear(); b.clear();
            FOR(j, 0, idx) {
                if ((j & ((1 << i) - 1)) == exact) {
                    for (int k : cmp[j]) {
                        if ((j >> i) & 1) a.push_back(k);
                        else b.push_back(k);
                    }
                }
            }

            while (a.size() > 1) {
                if (query(a.size() / 2, b.size(), a.data(), b.data())) a.erase(a.begin() + a.size() / 2, a.end());
                else a.erase(a.begin(), a.begin() + a.size() / 2);
            }
            while (b.size() > 1) {
                if (query(b.size() / 2, a.size(), b.data(), a.data())) b.erase(b.begin() + b.size() / 2, b.end());
                else b.erase(b.begin(), b.begin() + b.size() / 2);
            }

            int u = a[0], v = b[0];
            graph[u].push_back(v);
            graph[v].push_back(u);
            setRoad(u, v);
            break;
        }

        memset(visited, 0, sizeof(visited));
        FOR(i, 0, idx) cmp[i].clear();
    }
}
