#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll pref[101][101][101];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int l, m, n;
    cin >> l >> m >> n;
    FOR(i, 1, l + 1) FOR(j, 1, m + 1) FOR(k, 1, n + 1) {
        ll x;
        cin >> x;
        pref[i][j][k] = pref[i - 1][j][k] + pref[i][j - 1][k] + pref[i][j][k - 1] + x -
                        pref[i - 1][j - 1][k] - pref[i - 1][j][k - 1] - pref[i][j - 1][k - 1] +
                        pref[i - 1][j - 1][k - 1];
    }

    int a, b, c, x, y, z;
    while (cin >> a >> b >> c >> x >> y >> z) {
        cout << pref[x][y][z] -
                pref[a][y][z] - pref[x][b][z] - pref[x][y][c] +
                pref[a][b][z] + pref[a][y][c] + pref[x][b][c] -
                pref[a][b][c]
             << '\n';
    }
    return 0;
}