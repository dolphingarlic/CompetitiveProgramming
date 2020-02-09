/*
COCI 2020 Zapina
- Weird maths dp
- Basically dp1[i][j] = number of ways to assign j problems to the first
  i students so that none of then are happy
- The rest is left as an exercise to the reader
- Complexity: O(N^3)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

inline ll madd(ll a, ll b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

inline ll mmult(ll a, ll b) {
    a = (a * b) % MOD;
    return a;
}

ll chs[351][351], dp[351][351], dp2[351][351];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;

    FOR(i, 0, n + 1) chs[i][0] = 1;
    FOR(i, 1, n + 1) FOR(j, 1, i + 1) chs[i][j] = madd(chs[i - 1][j - 1], chs[i - 1][j]);

    dp[0][0] = dp2[0][0] = 1;
    FOR(i, 1, n + 1) FOR(j, 0, n + 1) {
        FOR(k, 0, j + 1) {
            if (k != i) dp[i][j] = madd(dp[i][j], mmult(dp[i - 1][j - k], chs[j][k]));
            dp2[i][j] = madd(dp2[i][j], mmult(dp2[i - 1][j - k], chs[j][k]));
        }
    }

    ll ans = 0;
    FOR(i, 1, n + 1) FOR(j, 0, n - i + 1) {
        ans = madd(ans, mmult(mmult(mmult(dp[i - 1][j], chs[n][j]), chs[n - j][i]), dp2[n - i][n - j - i]));
    }
    cout << ans;
    return 0;
}