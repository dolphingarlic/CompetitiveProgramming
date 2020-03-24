#include "Anthony.h"

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

namespace {

vector<int> X, perm = {0, 1, 0, 0, 1, 1};
vector<pair<int, int>> graph[20000];

void mark_tree(int node = 0, int par_id = -1, int depth = 0) {
    if (~par_id) X[par_id] = perm[depth];
    for (pair<int, int> i : graph[node]) if (i.second != par_id) {
        if (graph[node].size() == 2)
            mark_tree(i.first, i.second, (depth + 1) % 6);
        else
            mark_tree(i.first, i.second, 1 ^ perm[depth]);
    }
}

int visited[20000];

void mark_graph() {
    queue<int> q;
    q.push(0);
    visited[0] = 1;
    while (q.size()) {
        int curr = q.front();
        q.pop();
        for (pair<int, int> i : graph[curr]) if (!visited[i.first]) {
            X[i.second] = (visited[curr] - 1) % 3;
            visited[i.first] = visited[curr] + 1;
            q.push(i.first); 
        } else X[i.second] = (visited[i.first] - 1) % 3;
    }
}

}  // namespace

vector<int> Mark(int N, int M, int A, int B, vector<int> U, vector<int> V) {
    FOR(i, 0, M) {
        graph[U[i]].push_back({V[i], i});
        graph[V[i]].push_back({U[i], i});
    }

    X.resize(M);
    if (B) mark_tree();
    else mark_graph();
    return X;
}
