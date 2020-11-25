#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
using namespace std;
typedef long long ll;
 
ll dp[3001][3001];
 
int main() {
    int h, w;
    cin >> h >> w;
    dp[0][0] = 1;
    FOR(i, 0, h + 1) {
        FOR(j, 0, w + 1) {
            if(i == 0 || j == 0) dp[i][j] = 1;
            else {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
                dp[i][j] = (dp[i][j] + 4ll * j * dp[i - 1][j - 1]) % MOD;
                if(j > 1) dp[i][j] = (dp[i][j] + 1ll * (1ll * j * (j - 1) / 2) * dp[i - 1][j - 2]) % MOD;
                if(i > 1) dp[i][j] = (dp[i][j] + 1ll * j * (i - 1) * dp[i - 2][j - 1]) % MOD;
            }
        }
    }
    cout << dp[h][w] - 1 << '\n';
     return 0;
}