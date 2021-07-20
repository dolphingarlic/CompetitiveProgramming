#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll w[20];
pair<int, ll> dp[1 << 20];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    ll x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) cin >> w[i];
    dp[0] = {1, 0};
    for (int mask = 1; mask < (1 << n); mask++) {
        dp[mask] = {INT_MAX, 0};
        for (int i = 0; i < n; i++) if (mask & (1 << i)) {
            int sm = dp[mask ^ (1 << i)].second + w[i];
            if (sm <= x)
                dp[mask] = min(dp[mask], {dp[mask ^ (1 << i)].first, sm});
            else
                dp[mask] = min(dp[mask], {dp[mask ^ (1 << i)].first + 1, w[i]});
        }
    }
    cout << dp[(1 << n) - 1].first;
    return 0;
}