#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll ans = 0, dp[32][300001];
int colour[300001];
vector<int> graph[300001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    FOR(i, 1, n + 1) {
        int x;
        cin >> x;
        colour[i] = (1 << (x - 1));
        dp[colour[i]][i] = 1;
    }
    FOR(i, 0, m) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    FOR(i, 1, (1 << k)) {
        FOR(j, 1, n + 1) {
            if (colour[j] & i) {
                for (int k : graph[j]) {
                    if (colour[k] & (i - colour[j])) {
                        ans += dp[i - colour[j]][k];
                        dp[i][j] += dp[i - colour[j]][k];
                    }
                }
            }
        }
    }

    cout << ans << '\n';
    return 0;
}