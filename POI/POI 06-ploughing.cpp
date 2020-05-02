/*
POI 2006 Ploughing
- We have 3 cases
    - 1: The last ploughed strip is a single square
    - 2: The last ploughed strip is horizontal
    - 3: The last ploughed strip is vertical
- For case 1, we will always do exactly N - 1 horizontal and M - 1 vertical ploughs,
  so we set the upperbound of the answer to be N + M - 1
- For case 2 (since case 3 is just case 2 rotated by 90 degrees), we will do exactly N - 1 horizontal
  ploughs before the last one
    - This means whenever we can make a horizontal plough, we do it
    - When we can't, then we plough on of the vertical strips
    - To figure out which one we should plough, we use dp
    - dp[i][j] = The minimum number of vertical ploughs needed if the strips [i, j] aren't ploughed yet
- Complexity: O(N^2)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[2001][2001], k;
int dp[2001][2001];

ll horiz(int x, int y1, int y2) { return a[x][y2] + a[x - 1][y1 - 1] - a[x][y1 - 1] - a[x - 1][y2]; }
ll vert(int y, int x1, int x2) { return a[x2][y] + a[x1 - 1][y - 1] - a[x1 - 1][y] - a[x2][y - 1]; }

int calc(int x1, int y1, int x2, int y2) {
    if (x1 > x2) return 0;
    if (~dp[y1][y2]) return dp[y1][y2];
    if (k >= horiz(x1, y1, y2)) return dp[y1][y2] = calc(x1 + 1, y1, x2, y2);
    if (k >= horiz(x2, y1, y2)) return dp[y1][y2] = calc(x1, y1, x2 - 1, y2);

    dp[y1][y2] = INT_MAX;
    if (k >= vert(y1, x1, x2)) dp[y1][y2] = min(dp[y1][y2], calc(x1, y1 + 1, x2, y2) + 1);
    if (k >= vert(y2, x1, x2)) dp[y1][y2] = min(dp[y1][y2], calc(x1, y1, x2, y2 - 1) + 1);
    return dp[y1][y2]; 
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> k >> n >> m;
    swap(n, m);
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        cin >> a[i][j];
        a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    }

    int ans = n + m - 1;
    memset(dp, -1, sizeof(dp));
    ans = min(ans, calc(1, 1, n, m) + n);
    FOR(i, 1, max(n, m) + 1) FOR(j, 1, i) swap(a[i][j], a[j][i]);
    memset(dp, -1, sizeof(dp));
    ans = min(ans, calc(1, 1, m, n) + m);
    cout << ans;
    return 0;
}