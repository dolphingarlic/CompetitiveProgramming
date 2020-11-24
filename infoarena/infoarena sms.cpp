/*
Infoarena sms
- dp[i] = The EV of the time it takes to type character i after having typed i - 1 characters
        = pC[s[i] - 'a'] * 1 + pI[s[i] - 'a'] * (dp[i] + 2) + pB[s[i] - 'a'] * (dp[i - 1] + dp[i] + 1)
        = (1 + pI[s[i] - 'a'] + pB[s[i] - 'a'] * dp[i - 1]) / pC[s[i] - 'a']
- By linearity of expectation, the answer = sum(dp[i])
- Complexity: O(N)
*/

#include <bits/stdc++.h>
using namespace std;

double pC[26], pI[26], pB[26];

int main() {
    ifstream cin("sms.in");
    ofstream cout("sms.out");
    int n, k;
    string s;
    cin >> n >> k >> s;
    for (int i = 0; i < k; i++) cin >> pC[i] >> pI[i] >> pB[i];
    double ans = 0, prv = 0;
    for (int i = 0; i < n; i++) {
        double nxt = (1 + pI[s[i] - 'a'] + pB[s[i] - 'a'] * prv) / pC[s[i] - 'a'];
        ans += nxt;
        prv = nxt;
    }
    cout << fixed << setprecision(6) << ans;
    return 0;
}