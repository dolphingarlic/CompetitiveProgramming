/*
NOI.sg 2008 Gecko
- DP
- Complexity: O(NM)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[502], dp[502][502];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            cin >> a[i];
            dp[i][j] = max(dp[i - 1][j - 1], max(dp[i - 1][j], dp[i - 1][j + 1])) + a[i];
        }
    }
    cout << *max_element(dp[n] + 1, dp[n] + m + 1);
    return 0;
}