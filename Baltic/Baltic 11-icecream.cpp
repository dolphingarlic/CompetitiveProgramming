#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

bool graph[201][201];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, m) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = graph[b][a] = true;
    }

    int ans = 0;
    FOR(i, 1, n + 1) FOR(j, i + 1, n + 1) FOR(k, j + 1, n + 1) {
        if (!(graph[i][j] || graph[j][k] || graph[i][k])) ans++;
    }

    cout << ans;
    return 0;
}