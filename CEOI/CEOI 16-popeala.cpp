/*
CEOI 2016 Popeala
- dp[i][j] = Minimum score if we split the first i tests into j subtasks
           = min(dp[k][j - 1] + sum_of_scores(k + 1, i))
- For each k, maintain the size of the prefix of the i tests such that
  at most k people pass all those tests
- For each such prefix, maintain the minimum dp value
    - We can just brute force this minimum, since it adds up to amortised
      O(T) for each contestant
- Complexity: O(NTS)
*/

#include <bits/stdc++.h>
using namespace std;

int points[20001], prv[20001][51], best[51], dp[20001][51];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, t, s;
    cin >> n >> t >> s;
    for (int i = 1; i <= t; i++) {
        cin >> points[i];
        points[i] += points[i - 1];
    }
    for (int j = 1; j <= n; j++) {
        string solved;
        cin >> solved;
        for (int i = 0; i < solved.size(); i++) {
            if (solved[i] == '1') prv[i + 1][j] = prv[i][j];
            else prv[i + 1][j] = i + 1;
        }
    }
    for (int i = 1; i <= t; i++) {
        prv[i][0] = i;
        sort(prv[i], prv[i] + n + 1);
    }

    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for (int j = 1; j <= s; j++) {
        memset(best, 0x3f, sizeof best);
        for (int i = 1; i <= t; i++) {
            for (int k = 0; k <= n; k++) {
                for (int l = prv[i - 1][k]; l < prv[i][k]; l++) {
                    best[k] = min(best[k], dp[l][j - 1] - points[l] * k);
                }
                dp[i][j] = min(dp[i][j], best[k] + points[i] * k);
            }
        }
        cout << dp[t][j] << '\n';
    }
    return 0;
}