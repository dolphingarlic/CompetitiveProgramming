// Hashing

#include <bits/stdc++.h>
#pragma GCC Optimize("unroll-loops")
#pragma GCC Optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;
typedef unsigned long long ll;

const ll P = 5;
ll mult = 1, nult = 1, target = 0;
vector<vector<ll>> mp, con, hashes, vert, horiz;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    mp.resize(n); con.resize(n);
    hashes.resize(n); vert.resize(m); horiz.resize(n);
    FOR(i, 0, n) {
        mp[i].resize(m); con[i].resize(m);
        hashes[i].resize(m); horiz[i].resize(m);
    }
    FOR(i, 0, m) vert[i].resize(n);

    FOR(i, 0, n) FOR(j, 0, m) {
        char c;
        cin >> c;
        mp[i][j] = (c == '*');
    }
    FOR(i, 0, a) FOR(j, 0, b) {
        char c;
        cin >> c;
        con[i][j] = (c == '*');
    }

    FOR(i, 0, b) mult *= P;
    FOR(i, 0, a) nult *= mult;

    // Find hashes of the grids
    ll bs = 1;
    for (int i = a - 1; ~i; i--) {
        ll temp = bs;
        for (int j = b - 1; ~j; j--) {
            target += temp * con[i][j];
            hashes[0][0] += temp * mp[i][j];
            temp *= P;
        }
        bs *= mult;
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
    return 0;
}