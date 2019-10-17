#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll dp[500][500];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    dp[0][1] = 1;
    FOR(i, 1, 10) {
        FOR(j, 1, 10) {
            FOR(k, 1, j + 2) dp[i][j] += dp[i - 1][k];
            cout << dp[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}