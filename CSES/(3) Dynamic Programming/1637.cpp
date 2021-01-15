#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;
 
ll dp[1000001];
 
int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    dp[0] = 0;
    FOR(i, 1, n + 1) {
        dp[i] = INT_MAX;
        int cp = i;
        while (cp != 0) {
            dp[i] = min(dp[i], dp[i - cp % 10] + 1);
            cp /= 10;
        }
    }
    cout << dp[n] << '\n';
    return 0;
}