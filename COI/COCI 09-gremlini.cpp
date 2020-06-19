/*
COCI 2010 Gremlini
- Let dp[i][j][k] = Minimum time to get 2^i ancestors of gremlin j
                    if we start with a single gremlin k
- Since N is very small and T is very big, we can compute this in
  O(N^3 log T) time
- dp[i][j][k] = min(dp[i - 1][j][l] + dp[i - 1][l][k] for each l)
    - (Kinda like Floyd-Warshall)
- Since all times are positive, we can loop i down from ceil(log T)
  to 0 to find whether the i-th bit of the answer can be 1
- Complexity: O(N^3 log T)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, v[1002];
ll t, y[101], dp[51][101][101], nxt[101], curr[101];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> t;
    memset(dp, 0x3f, sizeof(dp));
    FOR(i, 1, n + 1) {
        int k;
        cin >> k >> y[i];
        FOR(j, 1, k + 1) cin >> v[j];
        FOR(j, 1, k + 1) {
            ll x;
            cin >> x;
            dp[0][v[j]][i] = min(dp[0][v[j]][i], x + y[i]);
        }
    }

    int p = 1;
    for (; (1ll << p) <= t; p++) {
        FOR(i, 1, n + 1) FOR(j, 1, n + 1) FOR(k, 1, n + 1) {
            dp[p][i][j] = min(dp[p][i][j], dp[p - 1][i][k] + dp[p - 1][k][j]);
        }
    }

    ll ans = 0;
    for (p--; ~p; p--) {
        ll mn = LLONG_MAX;
        memset(nxt, 0x3f, sizeof(nxt));
        FOR(i, 1, n + 1) FOR(j, 1, n + 1) {
            nxt[i] = min(nxt[i], curr[j] + dp[p][i][j]);
            mn = min(mn, nxt[i]);
        }
        if (mn <= t) {
            ans += (1ll << p);
            FOR(i, 1, n + 1) curr[i] = nxt[i];
        }
    }
    cout << ans;
    return 0;
}