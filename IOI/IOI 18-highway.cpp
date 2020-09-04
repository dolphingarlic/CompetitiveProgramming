/*
IOI 2018 Highway
- First, find the path length S->T (1 query)
- Next, binary search for an edge on the path S->T (17 queries)
    - Let this edge be (u, v)
- Notice how S->T must lie on the BFS tree rooted at u and v
- This means that we can reduce the general graph to a tree
- When it's a tree, we can binary search on the BFS order for
  the deepest edges in each subtree that's a part of the path
  S->T and therefore find S and T (since they're at the ends
  of those edges) (at most 32 queries)
- Total: At most 50 queries
*/

#include "highway.h"

#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> graph[90000], ord[2];
bool visited[90000];
int ans[2];

void find_pair(int N, vector<int> U, vector<int> V, int A, int B) {
    int M = int(U.size());
    for (int i = 0; i < M; i++) {
        graph[U[i]].push_back({V[i], i});
        graph[V[i]].push_back({U[i], i});
    }

    vector<int> W(M, 0);
    long long path_len = ask(W) / A;

    int l = 0, r = M - 1;
    while (l != r) {
        int mid = (l + r) / 2;
        fill(W.begin(), W.end(), 0);
        for (int i = 0; i <= mid; i++) W[i] = 1;
        long long res = ask(W);
        if (res == path_len * A) l = mid + 1;
        else r = mid;
    }
    int m_edge = l, uu = U[l], vv = V[l];

    visited[uu] = visited[vv] = true;
    queue<pair<int, int>> q;
    q.push({uu, 0}); q.push({vv, 1});
    ord[0].push_back({uu, -1}); ord[1].push_back({vv, -1});
    while (q.size()) {
        int curr, sub;
        tie(curr, sub) = q.front();
        q.pop();
        for (pair<int, int> i : graph[curr]) {
            if (!visited[i.first] && i.second > m_edge) {
                visited[i.first] = true;
                ord[sub].push_back(i);
                q.push({i.first, sub});
            }
        }
    }

    for (int s = 0; s < 2; s++) {
        l = 0, r = ord[s].size() - 1;
        while (l != r) {
            int mid = (l + r) / 2;
            fill(W.begin(), W.end(), 1);
            W[m_edge] = 0;
            for (pair<int, int> i : ord[1 - s]) if (i.second != -1) W[i.second] = 0;
            for (int i = 1; i <= mid; i++) W[ord[s][i].second] = 0;
            long long dist = ask(W);
            if (dist == path_len * A) r = mid;
            else l = mid + 1;
        }
        ans[s] = ord[s][l].first;
    }

    answer(ans[0], ans[1]);
}
