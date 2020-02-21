#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#pragma GCC optimize("unroll-loops")
typedef long long ll;
using namespace std;

const ll MOD = 1234567;

inline ll inv_max(ll x) { return x * (x + 1) / 2; }

ll inv[32][32][32 * 33 / 2], dp[32][32 * 33 / 2][32 * 33 / 2];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    inv[0][0][0] = 1;
    FOR(i, 0, 32) FOR(j, 0, 32) FOR(k, 0, inv_max(32)) {
        if (i && k >= j) inv[i][j][k] = (inv[i][j][k] + inv[i - 1][j][k - j]) % MOD;
        if (j) inv[i][j][k] = (inv[i][j][k] + inv[i][j - 1][k]) % MOD;
    }

    dp[0][0][0] = 1;
    FOR(n, 0, 32) {
        FOR(l1, 0, n) {
            ll l2 = n - 1 - l1;
            FOR(q1, 0, inv_max(l1) + 1) FOR(q2, 0, inv_max(l2) + 1) {
                vector<ll> pref(inv_max(l1) + inv_max(l2) + 1);
                vector<ll> i2_opts;
                FOR(i2, 0, inv_max(l2) + 1) if (dp[l2][q2][i2])
                    i2_opts.push_back(i2);

                FOR(i1, 0, inv_max(l1) + 1) {
                    if (!dp[l1][q1][i1]) continue;
                    for (ll i2 : i2_opts)
                        pref[i1 + i2] = (pref[i1 + i2] + (dp[l1][q1][i1] * dp[l2][q2][i2]) % MOD) % MOD;
                }

                vector<ll> ic_opts;
                FOR(ic, 0, l1 * l2 + 1) if (inv[l1][l2][ic]) ic_opts.push_back(ic);

                ll q = q1 + q2 + n - 1;
                FOR(si, 0, inv_max(l1) + inv_max(l2) + 1) {
                    if (!pref[si]) continue;
                    for (ll ic : ic_opts) {
                        ll i = si + ic + l1;
                        dp[n][q][i] = (dp[n][q][i] + (pref[si] * inv[l1][l2][ic]) % MOD) % MOD;
                    }
                }
            }
        }
    }

    FOR(f, 0, 10) {
        ifstream cin(to_string(f) + "-sorting.in");
        ofstream cout(to_string(f) + "-sorting.out");

        ll n, x;
        cin >> n >> x;

        ll ans = 0;
        FOR(i, 0, inv_max(n) + 1)
            FOR(j, n - 1, min(inv_max(n), i * x) + 1)
                ans = (ans + dp[n][i][j - n + 1]) % MOD;
        cout << ans << '\n';

        cin.close();
        cout.close();
    }
    return 0;
}