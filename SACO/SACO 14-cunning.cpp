/*
SACO 2014 Cunning
- Just simulate the ball for each query
- Complexity: O(NQ)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

char g[1001][1001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) cin >> g[i][j];
    while (q--) {
        char c;
        cin >> c;
        if (c == 'U') {
            int x, y;
            char k;
            cin >> k >> x >> y;
            g[x][y] = k;
        } else {
            int x;
            cin >> x;
            FOR(i, 1, n + 1) {
                if (g[i][x] == '/') x--;
                else if (g[i][x] == '\\') x++;
            }
            cout << x << '\n';
        }
    }
    return 0;
}