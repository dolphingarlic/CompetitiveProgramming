/*
Baltic 2015 Tug of War
- If a spot has nobody willing to take it, it's not possible
- If a spot has exactly 1 person willing to take it, assign that person
- View this problem now as a bipartite graph, where each person is an edge between
  the left and right sides
- We use BFS to assign all these people and check that every untaken spot has
  someone available at all times
- We are then left with some disjoint simple cycles
- Notice how each cycle has a "weight" that can either be positive or negative
- We want to assign signs to these weights so that the sum is less than or equal to K
- Notice how this is the same as finding a subset such that |SUBSET_SUM - TOTAL_SUM| <= K
- We can use knapsack DP for this
- To speed stuff up, we use as bitset
- Complexity: O(NK/64)
*/

#include <bits/stdc++.h>
using namespace std;

multiset<pair<int, int>> graph[60001];
bool visited[60001];
bitset<600001> possible;
int tot = 0, sm = 0;

void dfs(int node) {
    visited[node] = true;
    if (!graph[node].size()) return;
    int nxt, cost;
    tie(nxt, cost) = *graph[node].begin();

    tot += cost;
    if (!visited[nxt]) {
        graph[nxt].erase(graph[nxt].find({node, -cost}));
        graph[node].clear();
        dfs(nxt);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= 2 * n; i++) {
        int l, r, s;
        scanf("%d %d %d", &l, &r, &s);
        graph[l].insert({n + r, s});
        graph[n + r].insert({l, -s});
    }

    queue<int> q;
    for (int i = 1; i <= 2 * n; i++) {
        if (graph[i].size() == 1) q.push(i);
        if (graph[i].size() == 0) return printf("NO\n"), 0;
    }
    while (q.size()) {
        int curr = q.front();
        q.pop();
        if (graph[curr].size() == 0) return printf("NO\n"), 0;
        int nxt, cost;
        tie(nxt, cost) = *graph[curr].begin();
        tot += cost;

        graph[curr].clear();
        graph[nxt].erase(graph[nxt].find({curr, -cost}));
        if (graph[nxt].size() == 1) q.push(nxt);
    }

    vector<int> items;
    if (tot) items.push_back(abs(tot));
    for (int i = 1; i <= 2 * n; i++) if (!visited[i] && graph[i].size()) {
        tot = 0;
        graph[i].erase(graph[i].begin());
        dfs(i);
        if (tot) items.push_back(abs(tot));
    }
    sm = accumulate(items.begin(), items.end(), 0);

    possible[0] = 1;
    for (int i : items) possible |= possible << i;
    for (int i = 0; i <= sm; i++) if (possible[i] && abs(2 * i - sm) <= k) return printf("YES\n"), 0;
    printf("NO\n");
    return 0;
}