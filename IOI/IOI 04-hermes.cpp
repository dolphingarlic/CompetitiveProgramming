#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int dp[4][2001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, 2001) FOR(j, 0, 4) dp[j][i] = (1<<30);
    dp[0][1000] = dp[1][1000] = 0;
    int px = 1000, py = 1000;
    FOR(_, 0, n) {
        int x, y;
        cin >> x >> y;
        x += 1000, y += 1000;
        FOR(i, 0, 2001) {
            dp[2][i] = min(dp[2][i], dp[0][i] + abs(y - py));
            dp[3][i] = min(dp[3][i], dp[1][i] + abs(x - px));
            dp[2][px] = min(dp[2][px], dp[1][i] + abs(i - y));
            dp[3][py] = min(dp[3][py], dp[0][i] + abs(i - x));
        }
        FOR(i, 0, 2001) {
            dp[0][i] = dp[2][i], dp[1][i] = dp[3][i];
            dp[2][i] = dp[3][i] = (1<<30);
        }
        px = x, py = y;
    }
    
    cout << min(*min_element(dp[0], dp[0] + 2001), *min_element(dp[1], dp[1] + 2001));
    return 0;
}
