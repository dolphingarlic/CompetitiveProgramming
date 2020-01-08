#include "Annalib.h"
#include <bits/stdc++.h>
using namespace std;

static vector<int> graph[100001];
static int val[100001];

static void dfs(int node, int parent) {
    val[node] = val[parent] ^ (parent < node);
    Flag(node, val[node]);
    for (int i : graph[node]) if (i != parent) dfs(i, node);
}


void Anna(int K, int N, int T, int A[], int B[]) {
    for (int i = 0; i < N - 1; i++) {
        graph[A[i]].push_back(B[i]);
        graph[B[i]].push_back(A[i]);
    }
    dfs(T, 0);
}
