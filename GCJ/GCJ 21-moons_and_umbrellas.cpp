#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll dp[1000][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case #" << tc << ": ";
        int x, y;
        string s;
        cin >> x >> y >> s;
        if (s[0] == 'C') dp[0][0] = INT_MAX;
        else dp[0][0] = 0;
        if (s[0] == 'J') dp[0][1] = INT_MAX;
        else dp[0][1] = 0;
        for (int i = 1; i < s.size(); i++) {
            dp[i][0] = dp[i][1] = INT_MAX;
            if (s[i] != 'C')
                dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + x);
            if (s[i] != 'J')
                dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + y);
        }
        cout << min(dp[s.size() - 1][0], dp[s.size() - 1][1]) << '\n';
    }
    return 0;
}
