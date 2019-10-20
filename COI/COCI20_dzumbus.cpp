#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m;
vector<int> graph[1001];
ll dp[3][1001][1001], c[1001];

void dfs(int node, int parent) {
    dp[1][node][0] = c[node];
    dp[2][node][0] = 0;
    for (int i : graph[node]) {
        if (i != parent) {
            dfs(i, node);
            FOR(j, 1, n + 1) {
                if (j > 1) dp[0][node][j] = min(dp[1][i][j - 2], dp[0][i][j - 1]) + c[node];
                dp[1][node][j] = dp[2][i][j] + c[node];
                dp[2][node][j] = min(dp[2][i][j], dp[0][i][j]);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, n + 1) cin >> c[i];
    FOR(i, 0, m) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    FOR(i, 1, n + 1) {
        fill(dp[0][i], dp[0][i] + 1001, INT_MAX);
        fill(dp[1][i], dp[1][i] + 1001, INT_MAX);
        fill(dp[2][i], dp[2][i] + 1001, INT_MAX);
    }

    int root;
    FOR(i, 1, n + 1) if (graph[i].size() == 1) root = i;

    if (n != 1) dfs(root, -1);

    int q;
    cin >> q;
    while (q--) {
        ll d;
        cin >> d;
        if (n == 1) {
            cout << "0\n";
            continue;
        }
        int l = 2, r = n;
        while (l != r) {
            int mid = (l + r + 1) / 2;
            if (min(dp[0][root][mid], dp[2][root][mid]) <= d) l = mid;
            else r = mid - 1;
        }
        if (min(dp[0][root][l], dp[2][root][l]) <= d) cout << l << '\n';
        else cout << "0\n";
    }
    return 0;
}