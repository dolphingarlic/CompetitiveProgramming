#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MX = 1e6;

int dp[MX + 1][2];
vector<int> factors[MX + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int i = 2; i <= MX; i++) {
        for (int j = i + i; j <= MX; j += i)
            factors[j].push_back(i);
    }
    dp[2][0] = 1;
    for (int i = 3; i <= MX; i++) {
        dp[i][0] = dp[i][1] = 1;
        for (int j : factors[i]) {
            dp[i][0] = max(dp[i][0], dp[j - 1][0] + 1);
            if (j * 2 != i)
                dp[i][1] = max(dp[i][1], dp[j - 1][0] + 1);
        }
    }
    int t;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        int n;
        cin >> n;
        cout << "Case #" << test << ": " << dp[n][1] << '\n';
    }
    return 0;
}
