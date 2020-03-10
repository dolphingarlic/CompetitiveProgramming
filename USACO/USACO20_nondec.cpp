#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

int n, k, a[1001];
ll dp[1001][1001], pref[1001][1001];

ll bit[1001][1001];
void update(int tree, int pos, ll val) {
    for (; pos <= n; pos += (pos & (-pos))) bit[tree][pos] += val;
}
ll query(int tree, int pos) {
    ll ans = 0;
    for (; pos; pos -= (pos & (-pos))) ans += bit[tree][pos];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // freopen("nondec.in", "r", stdin);
    // freopen("nondec.out", "w", stdout);
    cin >> n >> k;
    FOR(i, 1, n + 1) cin >> a[i];

    FOR(i, 1, k + 1) {
        FOR(j, 1, n + 1) {
            if (a[j] == i) {
                dp[j][j] = 1;
                update(j, j, 1);

                for (int l = j - 1; l; l--) {
                    dp[j][l] = query(l, j - 1) + 1;
                    update(j, l, dp[j][l]);
                }
            }
        }
    }

    FOR(i, 1, n + 1) {
        FOR(j, 1, i + 1) cout << dp[i][j] << ' ';
        cout << '\n';
    }

    FOR(i, 1, n + 1) pref[i][i] = 1;
    FOR(i, 1, n + 1) FOR(j, i + 1, n + 1) {
        pref[i][j] = (pref[i][j - 1] + dp[j][i]) % MOD;
        cout << i << ' ' << j << ' ' << pref[i][j] << '\n';
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;

        cout << (pref[l][r] + 1) % MOD << '\n';
    }
    return 0;
}