#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int dp[1500][2], ord[1500][2], ans = 0;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    // freopen("logs.in", "r", stdin);
    // freopen("logs.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, m) ord[i][0] = i;

    FOR(i, 0, n) {
        string s;
        cin >> s;
        int l = 0, r = m - 1;
        FOR(j, 0, m) {
            if (s[ord[j][0]] == '0') {
                dp[ord[j][0]][1] = 0;
                ord[r--][1] = ord[j][0];
            } else {
                dp[ord[j][0]][1] = dp[ord[j][0]][0] + 1;
                ord[l++][1] = ord[j][0];
            }
        }
        FOR(j, 0, m) ord[j][0] = ord[j][1];
        FOR(j, 0, m) dp[j][0] = dp[j][1];

        FOR(j, 0, m) ans = max(ans, (j + 1) * dp[ord[j][0]][0]);
    }

    cout << ans;
    return 0;
}