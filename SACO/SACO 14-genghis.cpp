/*
SACO 2014 Genghis
- dp[i][j] = Minimum cost to construct a BST using a[i..j] and searching
             for numbers from a[i - 1] + 1 to a[j + 1] - 1
           = min(dp[i][k - 1] + dp[k + 1][j]) + a[j + 1] - a[i - 1] - 1
             for each k from i to j
- Complexity: O(K^3)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[302], dp[302][302];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    a[m + 1] = n + 1;
    FOR(i, 1, m + 1) cin >> a[i];
    sort(a, a + m + 2);

    FOR(k, 0, m) {
        FOR(i, 1, m - k + 1) {
            int j = i + k, mn = INT_MAX;
            FOR(l, i, j + 1) mn = min(mn, dp[i][l - 1] + dp[l + 1][j]);
            dp[i][j] = mn + a[j + 1] - a[i - 1] - 1;
        }
    }
    cout << dp[1][m];
    return 0;
}