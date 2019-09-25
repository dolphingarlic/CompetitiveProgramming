#include "dreaming.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;
 
vector<pair<int, int>> graph[100001];
bool visited[100001];
 
struct Node {
    int path, child, edge;
} dp[100001];
int curr_max = -1, curr_max1_c = -1, curr_max2_c = -1, curr_max_node = -1,
    curr_max1_edge = 0, curr_max2_edge = 0;
int r[100001], cmp[100001], ans = 0, indx = 0;
 
void ff(int node, int component, int parent = -1) {
    visited[node] = true;
    cmp[node] = component;
    for (auto& i : graph[node]) {
        if (i.first == parent) continue;
        ff(i.first, component, node);
    }
}
 
void dfs(int node) {
    visited[node] = true;
 
    int max1 = 0, max2 = 0, max1_c = -1, max2_c = -1, max1_edge = 0,
        max2_edge = 0;
    for (auto& i : graph[node]) {
        if (visited[i.first]) continue;
        dfs(i.first);
        if (dp[i.first].path + i.second >= max1) {
            max2 = max1;
            max2_c = max1_c;
            max2_edge = max1_edge;
            max1 = dp[i.first].path + i.second;
            max1_c = i.first;
            max1_edge = i.second;
        } else if (dp[i.first].path + i.second >= max2) {
            max2 = dp[i.first].path + i.second;
            max2_c = i.first;
            max2_edge = i.second;
        }
    }
 
    dp[node] = {max1, max1_c, max1_edge};
    if (max1 + max2 > curr_max) {
        curr_max = max1 + max2;
        curr_max1_c = max1_c;
        curr_max2_c = max2_c;
        curr_max_node = node;
        curr_max1_edge = max1_edge;
        curr_max2_edge = max2_edge;
    }
}
 
int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
    FOR(i, 0, M) {
        graph[A[i]].push_back({B[i], T[i]});
        graph[B[i]].push_back({A[i], T[i]});
    }
 
    fill(visited, visited + N, false);
    FOR(i, 0, N) if (!visited[i]) ff(i, indx++);
    fill(visited, visited + N, false);
 
    FOR(i, 0, N) {
        if (!visited[i]) {
            curr_max = -1, curr_max1_c = -1, curr_max2_c = -1,
            curr_max_node = -1, curr_max1_edge = 0, curr_max2_edge = 0;
            dfs(i);
 
            int x = dp[curr_max1_c].path + curr_max1_edge;
            int y =
                (curr_max2_c == 0 ? 0 : dp[curr_max2_c].path + curr_max2_edge);
 
            while (x > y && y + dp[curr_max_node].edge < x) {
                y += dp[curr_max_node].edge;
                x -= dp[curr_max_node].edge;
                curr_max_node = dp[curr_max_node].child;
            }
 
            r[cmp[curr_max_node]] = max(y, x);
            ans = max(ans, x + y);
        }
    }
    sort(r, r + indx, greater<int>());
 
    return max(ans, max((indx > 2 ? r[1] + r[2] + 2 * L : 0),
                        max((indx > 1 ? r[0] + r[1] + L : 0), r[0])));
}