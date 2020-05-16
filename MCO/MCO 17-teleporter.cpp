/*
MCO 2017 Teleporters
- Connected component DP
- See comments in code
- Complexity: O(N^2)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll dp[2001][2001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string S;
    int s, e, n;
    cin >> S >> s >> e;
    n = S.size();

    int st = 0, en = 0;
    dp[0][0] = 1;
    FOR(i, 1, n + 1) {
        FOR(j, 1, i + 1) {
            if (i == s) {
                // We move from i to something greater than i
                // That "greater than i" isn't present yet
                if (S[i - 1] != 'L') dp[i][j] += dp[i - 1][j - 1];
                // We move from i to something less than i.
                // That "less than i" must already be present
                if (S[i - 1] != 'R') dp[i][j] += dp[i - 1][j];
            } else if (i == e) {
                // We either append i to the end of a component or create an end
                // component. We can do it no matter what S[i - 1] is since we
                // don't go anywhere after this
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
            } else {
                // We move to something greater than i. We either create a new
                // component or append to an existing one from the back
                if (S[i - 1] != 'L')
                    dp[i][j] += max(0, j - st - en) * dp[i - 1][j - 1] +
                                (j - en) * dp[i - 1][j];
                // We move to something less than i. We either join 2 components
                // or append to an existing one from the front 
                if (S[i - 1] != 'R')
                    dp[i][j] += j * dp[i - 1][j + 1] + (j - st) * dp[i - 1][j];
            }
            dp[i][j] %= MOD;
        }
        if (i == s) st++;
        if (i == e) en++;
    }
    cout << dp[n][1];
    return 0;
}