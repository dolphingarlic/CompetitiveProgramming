#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int dp[20001][2];
pair<int, int> s[20001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    s[0] = {1, 1};
    FOR(i, 1, n + 1) {
        cin >> s[i].first >> s[i].second;
        int len = s[i].second - s[i].first;
        dp[i][0] = min(dp[i - 1][0] + abs(s[i - 1].first - s[i].second) + len, dp[i - 1][1] + abs(s[i - 1].second - s[i].second) + len);
        dp[i][1] = min(dp[i - 1][0] + abs(s[i - 1].first - s[i].first) + len, dp[i - 1][1] + abs(s[i - 1].second - s[i].first) + len);
    }

    cout << min(dp[n][0] + n - s[n].first, dp[n][1] + n - s[n].second) + n - 1;
    return 0;
}