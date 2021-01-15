#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;
 
char a[1000][1000];
int dp[1000][1000];
 
int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) FOR(j, 0, n) cin >> a[i][j];
    dp[0][0] = (a[0][0] != '*');
    FOR(i, 0, n) FOR(j, 0, n) {
        if (i || j) {
            if (a[i][j] == '*') dp[i][j] = 0;
            else dp[i][j] = ((i > 0 ? dp[i - 1][j] : 0) + (j > 0 ? dp[i][j - 1] : 0)) % MOD;
        }
    }
    cout << dp[n - 1][n - 1] << '\n';
    return 0;
}