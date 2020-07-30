/*
Baltic 2012 Brackets
- Notice how we basically only care about changing '(' to ')'
- Let the "height" of a bracket sequence be the number of unpaired '('
- dp[i][j] = The number of ways to change several '(' in the first
             i brackets such that the height is never negative and the
             final height is j
           = dp[i - 1][j + 1] + (s[i] == '(' ? dp[i - 1][j - 1] : 0)
- Notice how dp[i] only depends on 2 values in dp[i - 1], so we don't
  have to store the first dimension in our DP array
    - Also, we can use a stack to store our DP, since we know which
      index the maximum non-zero value is at
- This is somehow fast enough to pass
- Complexity: O(N^2)
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 9;

int dp[30001], tail = 1;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s;
    cin >> n >> s;
    dp[0] = 1;
    for (char c : s) {
        if (c == ')') tail--;
        else {
            dp[tail] = (tail > 1 ? dp[tail - 2] : 0);
            for (int i = tail - 1; i > 1; i--) {
                dp[i] += dp[i - 2];
                if (dp[i] >= MOD) dp[i] -= MOD;
            }
            tail++;
        }
    }
    cout << dp[tail - 1];
    return 0;
}