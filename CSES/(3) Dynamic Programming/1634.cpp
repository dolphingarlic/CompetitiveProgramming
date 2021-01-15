#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
ll a[100], dp[1000001];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    fill(dp + 1, dp + m + 1, INT_MAX);
    dp[0] = 0;
    FOR(i, 0, n) cin >> a[i];
    FOR(i, 1, m + 1) FOR(j, 0, n) if (i - a[j] > -1) dp[i] = min(dp[i], dp[i - a[j]] + 1);
    if (dp[m] >= INT_MAX) cout << -1;
    else cout << dp[m];
    return 0;
}