#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll add(ll A, ll B) {
    A += B;
    if (A >= MOD) A -= MOD;
    return A;
}

ll mult(ll A, ll B) {
    A *= B;
    A %= MOD;
    return A;
}

ll expo(ll base, ll pw) {
    ll ans = 1;
    while (pw) {
        if (pw & 1) ans = ans * base % MOD;
        base = base * base % MOD;
        pw >>= 1;
    }
    return ans;
}

int n;
ll dp[2001][2001], ps[2001][2001];
string h[2001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    FOR(i, 1, n + 1) cin >> h[i];

    dp[0][0] = 1;
    int d2 = expo(2, MOD - 2), d4 = mult(d2, d2);
    FOR(i, 1, n + 1) dp[0][i] = (h[i][0] == '.') * d2;

    FOR(j, 1, n) {
        FOR(i, 1, n + 1) ps[j - 1][i] = add(dp[j - 1][i - 1] * (h[i][j - 1] == '.'), ps[j - 1][i - 1]);
        FOR(i, 0, n + 1) {
            dp[j][i] = dp[j - 1][i];
            if (i && h[i][j] == '.') dp[j][i] = add(dp[j][i], mult(d4, ps[j - 1][i]));
        }
    }

    int ans = 0;
    int ct = 0;
    FOR(i, 1, n + 1) for (char c : h[i]) if (c == '.') ct++;
    ct = expo(2, ct);
    FOR(i, 0, n) if (h[i + 1][n - 1] == '.') ans = add(ans, mult(d2, dp[n - 1][i]));

    ans = add(ans, dp[n - 1][n]);
    cout << mult(ans, ct);
    return 0;
}