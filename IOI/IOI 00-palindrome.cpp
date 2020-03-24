#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int dp[5000][2];
int temp_dp[5000];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    string s;
    cin >> n >> s;

    FOR(i, 1, n) {
        FOR(j, 0, n) {
            if (s[j] == s[j + i]) temp_dp[j] = dp[j + 1][0];
            else temp_dp[j] = min(dp[j][1], dp[j + 1][1]) + 1;
        }

        FOR(j, 0, n) {
            dp[j][0] = dp[j][1];
            dp[j][1] = temp_dp[j];
        }
    }

    cout << dp[0][1] << '\n';
    return 0;
}