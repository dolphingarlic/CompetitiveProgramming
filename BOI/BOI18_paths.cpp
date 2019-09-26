#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll ans = 0;
int colour[100001], corr[6]{0, 1, 2, 4, 8, 16};
vector<int> graph[100001];

void dfs(int node, int path, int len = 0) {
    if (len) ans++;
    for (int i : graph[node]) {
        if (path & colour[i]) dfs(i, path - colour[i], len + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    int targ = (1<<k) - 1;
    FOR(i, 1, n + 1) {
        int x;
        cin >> x;
        colour[i] = corr[x];
    }
    FOR(i, 0, m) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    FOR(i, 1, n + 1) dfs(i, targ - colour[i]);

    cout << ans << '\n';
    return 0;
}