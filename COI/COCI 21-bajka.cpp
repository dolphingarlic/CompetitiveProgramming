#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int dp[2][300];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    string s, t;
    vector<int> pos;
    cin >> n >> m >> s >> t;
    for (int i = 0; i < n; i++) if (s[i] == t[0]) pos.push_back(i);
    for (int i = 1; i < m; i++) {
        pos.clear();
        for (int j = 0; j < n; j++) if (s[j] == t[i]) {
            pos.push_back(j);
            dp[i & 1][j] = INT_MAX / 2;
            if (j && s[j - 1] == t[i - 1]) {
                dp[i & 1][j] = min(dp[i & 1][j], dp[i - 1 & 1][j - 1] + 1);
            }
            if (j < n - 1 && s[j + 1] == t[i - 1]) {
                dp[i & 1][j] = min(dp[i & 1][j], dp[i - 1 & 1][j + 1] + 1);
            }
        }
        for (int j : pos) for (int k : pos) dp[i & 1][j] = min(dp[i & 1][j], dp[i & 1][k] + abs(k - j));
    }

    int ans = INT_MAX / 2;
    for (int i : pos) ans = min(ans, dp[m - 1 & 1][i]);
    if (ans == INT_MAX / 2) cout << -1;
    else cout << ans;
    return 0;
}