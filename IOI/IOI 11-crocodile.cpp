#include "crocodile.h"
#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
#define MAXN 100001
using namespace std;
 
vector<int> exits;
vector<pair<int, int>> graph[MAXN];
int visited[MAXN];
 
int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]) {
    FOR(i, 0, M) {
        graph[R[i][0]].push_back({R[i][1], L[i]});
        graph[R[i][1]].push_back({R[i][0], L[i]});
    }
    FOR(i, 0, K) exits.push_back(P[i]);
    fill(visited, visited + MAXN, 0);
    priority_queue<pair<int, int>> pq;  // Distance from an exit
    for (int i : exits) {
        pq.push({0, i});
        visited[i] = 1;
    }
 
    while (!pq.empty()) {
        int curr_node = pq.top().second, curr_cost = pq.top().first;
        pq.pop();
 
        if (visited[curr_node] == 0) {
            visited[curr_node]++;
        } else if (visited[curr_node] == 1) {
            if (curr_node == 0) return -curr_cost;
            visited[curr_node]++;
            for (pair<int, int> i : graph[curr_node]) pq.push({curr_cost - i.second, i.first});
        }
    }
}