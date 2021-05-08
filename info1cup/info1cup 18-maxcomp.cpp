/*
InfO(1) Cup 2018 MaxComp
- The optimal subset is just a path between two cells
- The answer is thus max(first cell - last cell - Manhattan distance - 1)
- Use 2D prefix minimums to find this
- Complexity: O(NM)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll grid[1001][1001], val[1001][1001][4], mn[1002][1002][4];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
            val[i][j][0] = grid[i][j] - i - j + 1;
            val[i][j][1] = grid[i][j] - m + j - i;
            val[i][j][2] = grid[i][j] + i + j - 1;
            val[i][j][3] = grid[i][j] + m - j + i;
        }
    
    ll ans = 0;
    memset(mn, 0x3f, sizeof mn);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            mn[i][j][0] = min({val[i][j][0], mn[i - 1][j][0], mn[i][j - 1][0]});
            ans = max(ans, val[i][j][0] - mn[i][j][0]);
        }
    for (int i = 1; i <= n; i++)
        for (int j = m; j; j--) {
            mn[i][j][1] = min({val[i][j][1], mn[i - 1][j][1], mn[i][j + 1][1]});
            ans = max(ans, val[i][j][1] - mn[i][j][1]);
        }
    for (int i = n; i; i--)
        for (int j = m; j; j--) {
            mn[i][j][2] = min({val[i][j][2], mn[i + 1][j][2], mn[i][j + 1][2]});
            ans = max(ans, val[i][j][2] - mn[i][j][2]);
        }
    for (int i = n; i; i--)
        for (int j = 1; j <= m; j++) {
            mn[i][j][3] = min({val[i][j][3], mn[i + 1][j][3], mn[i][j - 1][3]});
            ans = max(ans, val[i][j][3] - mn[i][j][3]);
        }
    cout << ans - 1;
    return 0;
}
