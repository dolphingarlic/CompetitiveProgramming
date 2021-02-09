/*
POI 2005 Template
- Same as amortized O(N), but we make a "KMP tree"
- The subree of node i would be the set of positions matching S[0 : i]
- We can thus use a linked list to keep track of gaps between matches
*/

#include <bits/stdc++.h>
using namespace std;

string s;
int p[500001], mx_gap = 1, ans, prv[500001], nxt[500001];
vector<int> graph[500001];
bool visited[500001];

void dfs(int node) {
    visited[node] = true;
    if (node && !visited[p[node - 1]]) {
        dfs(p[node - 1]);
        if (mx_gap <= node) ans = min(ans, node);
    }
    mx_gap = max(mx_gap, nxt[node] - prv[node]);
    nxt[prv[node]] = nxt[node];
    prv[nxt[node]] = prv[node];
    for (int i : graph[node]) if (!visited[i]) dfs(i);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> s;
    int n = s.size();
    graph[0].push_back(1);
    for (int i = 1; i < n; i++) {
        p[i] = p[i - 1];
        while (p[i] && s[i] != s[p[i]]) p[i] = p[p[i] - 1];
        if (s[i] == s[p[i]]) p[i]++;
        graph[p[i]].push_back(i + 1);
    }
    prv[0] = 0, nxt[0] = 1, prv[n] = n - 1, nxt[n] = n;
    for (int i = 1; i < n; i++) prv[i] = i - 1, nxt[i] = i + 1;
    ans = n;
    dfs(n);
    cout << ans;
    return 0;
}
