/*
POI 2004 Tournament
- Firstly, notice that in an SCC, if 1 node can win, all of them can
- Find all the SCCs in the graph and make the nodes in the ones with no incoming edges winners
- For each other node, they're a winner iff at least 1 winning node doesn't win against it
- We use a BFS to do this
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int cmp[100001], scc = 0;
vector<int> beats[100001], graph[100001], stck;
bool visited[100001], win_scc[100001];
set<int> can_win;

void dfs1(int node) {
    visited[node] = true;
    for (int i : graph[node])
        if (!visited[i]) dfs1(i);
    stck.push_back(node);
}

void dfs2(int node) {
    cmp[node] = scc;
    for (int i : beats[node]) {
        if (!cmp[i])
            dfs2(i);
        else if (cmp[i] != scc)
            win_scc[scc] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        int k;
        cin >> k;
        FOR(j, 0, k) {
            int v;
            cin >> v;
            beats[v].push_back(i);
            graph[i].push_back(v);
        }
    }

    FOR(i, 1, n + 1) if (!visited[i]) dfs1(i);
    while (stck.size()) {
        if (!cmp[stck.back()]) {
            win_scc[++scc] = true;
            dfs2(stck.back());
        }
        stck.pop_back();
    }

    queue<int> q;
    FOR(i, 1, n + 1) {
        visited[i] = false;
        if (win_scc[cmp[i]]) {
            q.push(i);
            can_win.insert(i);
            visited[i] = true;
        }
    }
    while (q.size()) {
        int curr = q.front();
        q.pop();

        int cnt = 0;
        for (int i : beats[curr]) cnt += (can_win.find(i) != can_win.end());
        if (cnt != can_win.size()) can_win.insert(curr);

        for (int i : graph[curr]) if (!visited[i]) {
            visited[i] = true;
            q.push(i);
        }
    }
    FOR(k, 0, 2) FOR(i, 1, n + 1) {
        int cnt = 0;
        for (int j : beats[i]) cnt += (can_win.find(j) != can_win.end());
        if (cnt != can_win.size()) can_win.insert(i);
    }

    cout << can_win.size() << ' ';
    for (int i : can_win) cout << i << ' ';
    return 0;
}