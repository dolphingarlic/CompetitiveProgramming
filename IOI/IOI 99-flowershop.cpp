#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int b[101][101];
pair<int, int> dp[101][101];

int main() {
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) cin >> b[i][j];
    
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) dp[i][j] = {-100000, -1};
    dp[0][0] = {0, 0};
    FOR(i, 1, n + 1) {
        FOR(j, i, m + 1) {
            FOR(k, i - 1, j) {
                if (dp[i - 1][k].first + b[i][j] > dp[i][j].first) {
                    dp[i][j] = {dp[i - 1][k].first + b[i][j], k};
                }
            }
        }
    }
    
    pair<int, int> best = *max_element(dp[n] + 1, dp[n] + m + 1);
    vector<int> seq;
    cout << best.first << '\n';
    seq.push_back(find(dp[n] + 1, dp[n] + m + 1, best) - dp[n]);
    for (int i = n - 1; i; i--) {
        seq.push_back(best.second);
        best = dp[i][best.second];
    }
    reverse(seq.begin(), seq.end());
    
    for (int i : seq) cout << i << ' ';
    return 0;
}
