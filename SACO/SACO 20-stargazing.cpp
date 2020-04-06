// Hashing

#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse4,avx2,fma,avx")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
using namespace std;
typedef unsigned int ll;

const ll MX = 5000, N = 1e7, P = 5;

ll mult = 1, nult = 1, target = 0;
bool mp[MX][MX], con[MX][MX];
ll hashes[MX][MX], vert[MX][MX], horiz[MX][MX], lps[N];
char s[N], t[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, m, a, b;
    cin >> n >> m >> a >> b;

    if (n == 1) {
        FOR(i, 0, m) cin >> s[i];
        FOR(i, 0, b) cin >> t[i];

        // Compute lps
        int len = 0;
        lps[0] = 0;
        int idx = 1;
        while (idx < b) {
            if (t[idx] == t[len]) {
                len++;
                lps[idx] = len;
                idx++;
            } else {
                if (len != 0) len = lps[len - 1];
                else {
                    lps[idx] = 0;
                    idx++;
                }
            }
        }

        // Begin KMP
        int i = 0, j = 0;
        while (i < m) {
            if (t[j] == s[i]) i++, j++;

            if (j == b) return cout << i - j << ' ' << 0, 0;

            if (i < m && t[j] != s[i]) {
                if (j != 0) j = lps[j - 1];
                else i++;
            }
        }
        cout << "-1 -1";
    } else {
        FOR(i, 0, n) {
            string s;
            cin >> s;
            FOR(j, 0, m) mp[i][j] = (s[j] == '*');
        }
        FOR(i, 0, a) {
            string s;
            cin >> s;
            FOR(j, 0, b) con[i][j] = (s[j] == '*');
        }

        FOR(i, 0, b) mult *= P;
        FOR(i, 0, a) nult *= mult;

        // Find hashes of the grids
        for (ll i = a, bs = 1; i; i--) {
            for (ll j = b; j; j--) {
                target += bs * con[i - 1][j - 1];
                hashes[0][0] += bs * mp[i - 1][j - 1];
                bs *= P;
            }
        }

        // Find hashes of rows and columns
        FOR(i, 0, n) {
            FOR(j, 0, b) horiz[i][0] = horiz[i][0] * P + mp[i][j];
            FOR(j, 1, m - b + 1) {
                horiz[i][j] = horiz[i][j - 1] * P + mp[i][j + b - 1] - mult * mp[i][j - 1];
            }
        }
        FOR(i, 0, m) {
            FOR(j, 0, a) vert[i][0] = vert[i][0] * mult + mp[j][i];
            FOR(j, 1, n - a + 1) {
                vert[i][j] = vert[i][j - 1] * mult + mp[j + a - 1][i] - nult * mp[j - 1][i];
            }
        }

        // Find hashes of other stuff with rolling hash
        FOR(i, 0, n - a + 1) {
            FOR(j, 0, m - b + 1) {
                if (!j && i) {
                    hashes[i][j] = hashes[i - 1][j] * mult + horiz[i + a - 1][j] - nult * horiz[i - 1][j];
                } else if (j) {
                    hashes[i][j] = hashes[i][j - 1] * P + vert[j + b - 1][i] - mult * vert[j - 1][i];
                }

                if (hashes[i][j] == target) return cout << j << ' ' << i, 0;
            }
        }
        cout << "-1 -1";
    }
    return 0;
}