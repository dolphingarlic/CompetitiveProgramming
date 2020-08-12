/*
InfO(1) Cup 2017 Easter Eggs
- Binary search on the DFS order of the tree for the largest prefix
  without an easter egg
- Complexity: log N queries
*/

#include <bits/stdc++.h>
#include "grader.h"
using namespace std;

vector<int> graph[513], ord;

void dfs(int node = 1, int parent = 0) {
    ord.push_back(node);
    for (int i : graph[node]) if (i != parent) dfs(i, node);
}

int findEgg(int N, vector<pair<int, int>> bridges) {
    for (int i = 1; i <= N; i++) graph[i].clear();
    ord.clear();
    for (pair<int, int> i : bridges) {
        graph[i.first].push_back(i.second);
        graph[i.second].push_back(i.first);
    }
    dfs();
    int l = 0, r = N - 1;
    while (l != r) {
        int mid = (l + r + 1) / 2;
        if (query(vector<int>(ord.begin(), ord.begin() + mid))) r = mid - 1;
        else l = mid;
    }
    return ord[l];
}
