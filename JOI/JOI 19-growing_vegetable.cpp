#include <bits/stdc++.h>
using namespace std;

const int INF = 1e6;

vector<int> has[4];
int dp[401][401][401][4];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        if (c == 'R') has[1].push_back(i);
        if (c == 'G') has[2].push_back(i);
        if (c == 'Y') has[3].push_back(i);
    }
    dp[0][0][0][1] = dp[0][0][0][2] = dp[0][0][0][3] = 0;
    for (int i = 0; i <= has[1].size(); i++)
        for (int j = 0; j <= has[2].size(); j++)
            for (int k = 0; k <= has[3].size(); k++) {
                if (i || j || k) dp[i][j][k][1] = dp[i][j][k][2] = dp[i][j][k][3] = INF;
                int tot = i + j + k;
                if (i) dp[i][j][k][1] = min(dp[i - 1][j][k][2], dp[i - 1][j][k][3]) + abs(has[1][i - 1] - tot);
                if (j) dp[i][j][k][2] = min(dp[i][j - 1][k][1], dp[i][j - 1][k][3]) + abs(has[2][j - 1] - tot);
                if (k) dp[i][j][k][3] = min(dp[i][j][k - 1][1], dp[i][j][k - 1][2]) + abs(has[3][k - 1] - tot);
            }
    int ans = *min_element(dp[has[1].size()][has[2].size()][has[3].size()] + 1, dp[has[1].size()][has[2].size()][has[3].size()] + 4);
    cout << dp[0][2][3][3] << '\n';
    if (ans >= INF) cout << -1;
    else cout << ans / 2;
    return 0;
}

/*
15
YYYRRRRRGGGGGGG

Answer: 23
*/
