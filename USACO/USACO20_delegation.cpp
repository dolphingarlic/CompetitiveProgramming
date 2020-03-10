#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[100001];
int k, dp[100001];
bool match_all[100001];

bool dfs(int node = 1, int parent = 0) {
    if (graph[node].size() == 1) {
        dp[node] = 1;
        match_all[node] = true;
        return true;
    }

    match_all[node] = false;

    bool possible = true;
    vector<int> c_paths;
    for (int i : graph[node]) {
        if (i != parent) {
            possible &= dfs(i, node);
            if (!possible) return false;
            c_paths.push_back(dp[i]);
        }
    }
    if (!(c_paths.size() & 1)) c_paths.push_back(0);
    sort(c_paths.begin(), c_paths.end());

    possible = false;
    int opt = -1;
    FOR(i, 0, c_paths.size()) {
        bool yes = true;
        for (int lptr = 0, rptr = c_paths.size() - 1; lptr < rptr; lptr++, rptr--) {
            if (lptr == i) lptr++;
            if (rptr == i) rptr--;
            yes &= (c_paths[lptr] + c_paths[rptr] >= k);
        }
        if (yes) {
            possible = true;
            opt = i;
            if (c_paths[opt] == 0) match_all[node] = true;
        }
    }

    if (possible) dp[node] = c_paths[opt] + 1;
    return possible;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ifstream cin("deleg.in");
    ofstream cout("deleg.out");

    int n;
    cin >> n;
    FOR(i, 1, n) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int l = 1, r = n - 1;
    while (l != r) {
        k = (l + r + 1) / 2;
        if (dfs() && (match_all[1] || ((graph[1].size() & 1) && dp[1] > k))) l = k;
        else r = k - 1;
    }
    cout << l << '\n';
    return 0;
}