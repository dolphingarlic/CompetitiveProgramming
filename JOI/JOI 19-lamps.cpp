#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

char s[100001], t[100001];
int dp[100001][3][2], mn[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) cin >> s[i];
    FOR(i, 1, n + 1) cin >> t[i];

    FOR(i, 0, 3) FOR(j, 0, 2) dp[0][i][j] = 1;
    FOR(i, 1, n + 1) {
        FOR(j, 0, 3) FOR(k, 0, 2) dp[i][j][k] = INT_MAX;
        if (t[i] == '0') {
            dp[i][0][0] = min(mn[i - 1] + 1, min(dp[i - 1][2][1], dp[i - 1][0][0]));
            dp[i][1][1] = min(mn[i - 1] + 1, min(dp[i - 1][2][0], dp[i - 1][1][1]));
        } else {

        }
    }
    return 0;
}