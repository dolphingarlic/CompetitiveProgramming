#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

bitset<500> grid[500], curr[500], temp[500];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int r, c, m;
    cin >> r >> c >> m;
    FOR(i, 0, r) FOR(j, 0, c) {
        char k;
        cin >> k;
        if (k == '.') {
            grid[i][c - j - 1] = 1;
            curr[i][c - j - 1] = 1;
        }
    }

    FOR(dir, 0, m) {
        char q;
        cin >> q;
        switch (q) {
            case 'N':
                FOR(i, 1, r) curr[i - 1] = curr[i];
                curr[r - 1].reset();
                break;
            case 'E':
                FOR(i, 0, r) curr[i] >>= 1;
                break;
            case 'S':
                for (int i = r - 1; i > 0; i--) curr[i] = curr[i - 1];
                curr[0].reset();
                break;
            case 'W':
                FOR(i, 0, r) curr[i] <<= 1;
                break;
            default:
                FOR(i, 0, r) temp[i].reset();

                FOR(i, 1, r) temp[i - 1] |= curr[i];
                for (int i = r - 1; i > 0; i--) temp[i] |= curr[i - 1];
                FOR(i, 0, r) temp[i] |= ((curr[i] << 1) | (curr[i] >> 1));

                FOR(i, 0, r) curr[i] = temp[i];
        }
        FOR(i, 0, r) curr[i] &= grid[i];
    }

    int ans = 0;
    FOR(i, 0, r) FOR(j, 0, c) ans += curr[i][j];
    cout << ans;
    return 0;
}