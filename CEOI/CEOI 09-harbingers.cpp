/*
CEOI 2009 Harbingers
- dp[i] = Minimum time to deliver the message from node i
        = S[i] + V[i] * to_root[i] + min(dp[parent] - V[i] * to_root[parent])
- Notice how these are linear functions, so we can use CHT
- Since this is a tree though, we need a way to "roll back" line insertions
- Since gradients are strictly decreasing, we can store our lines in an array
  acting as a stack
    - This is convenient for 2 reasons:
    - Firstly, it's super fast
    - Secondly, we can store the "deleted" lines in the array and just change
      the tail pointer
        - We "change" exactly 1 line when we insert a line, so we can just
          revert that one line and the tail pointer at the end of the DFS
- As with normal CHT, we can binary search for the insertion and query positions
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Line {
    ll m, c;
    ll operator()(ll x) { return m * x + c; }
} cht[100001];
int ptr = 0;

double intersect(Line A, Line B) {
    return double(B.c - A.c) / (A.m - B.m);
}

ll dp[100001], s[100001], v[100001], to_root[100001];
vector<pair<int, int>> graph[100001];

void dfs(int node, int parent = 1) {
    int l = 0, r = ptr;
    while (l != r) {
        int mid = (l + r) / 2;
        if (intersect(cht[mid], cht[mid + 1]) >= v[node]) r = mid;
        else l = mid + 1;
    }
    dp[node] = s[node] + v[node] * to_root[node] + cht[l](v[node]);

    Line curr = {-to_root[node], dp[node]};
    l = 0, r = ptr;
    while (l != r) {
        int mid = (l + r) / 2;
        if (intersect(cht[mid], cht[mid + 1]) >= intersect(cht[mid], curr)) r = mid;
        else l = mid + 1;
    }
    int prev_ptr = ptr;
    Line replaced = cht[l + 1];
    cht[l + 1] = curr;
    ptr = l + 1;

    for (pair<int, int> i : graph[node]) if (i.first != parent) {
        to_root[i.first] = to_root[node] + i.second;
        dfs(i.first, node);
    }

    cht[ptr] = replaced;
    ptr = prev_ptr;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].push_back({v, d});
        graph[v].push_back({u, d});
    }
    for (int i = 2; i <= n; i++) cin >> s[i] >> v[i];

    for (pair<int, int> i : graph[1]) {
        to_root[i.first] = i.second;
        dfs(i.first);
    }

    for (int i = 2; i <= n; i++) cout << dp[i] << " \n"[i == n];
    return 0;
}