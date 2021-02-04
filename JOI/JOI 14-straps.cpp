/*
JOI 2014 Straps
- It's optimal to attach every positive strap with at least 1 terminal
- Afterward, we want to find
    max((Attach K positive straps) + (Attach negative straps to get at least K terminals))
- This is just knapsack DP
- Complexity: O(N^2)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll dp[2001], pref[2001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, rem = 1;
    cin >> n;
    ll ans = 0;
    vector<int> pos;
    vector<pair<int, int>> neg;
    // Always take positive straps with at least one terminal
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (a) {
            if (b >= 0) ans += b, rem += a - 1;
            else neg.push_back({a, -b});
        } else if (b >= 0) pos.push_back(b);
    }
    // Attach as many positive straps with no terminals as possible
    sort(pos.begin(), pos.end());
    for (; rem > 1 && pos.size(); rem--) {
        ans += pos.back();
        pos.pop_back();
    }
    // Then do knapsack DP
    memset(dp, 0x3f, sizeof dp);
    dp[1] = 0;
    for (pair<int, int> i : neg)
        for (int j = n; j >= i.first; j--)
            dp[j] = min(dp[j], dp[j - i.first + 1] + i.second);
    ll mx = 0;
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + (i <= pos.size() ? pos[pos.size() - i] : 0);
        mx = max(mx, pref[i] - dp[i]);
    }
    cout << ans + mx << '\n';
    return 0;
}
