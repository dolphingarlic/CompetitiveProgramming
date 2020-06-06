/*
SACO 2008 Disgusting Banquet
- Aliens trick
- See NOI.sg 2019 Feast
- Complexity: O(N log MAX_A)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[50001], dp[50001];
int cnt[50001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, k, sm = 0;
    cin >> n >> k;
    FOR(i, 1, n + 1) {
        cin >> a[i];
        sm += a[i];
        a[i] *= -1;
    }

    ll l = 0, r = 3e14, ans = 0;
    while (l != r) {
        ll mid = (l + r) / 2;

        ll local_max = 0, local_max_cnt = 0;
        FOR(i, 1, n + 1) {
            local_max += a[i];
            if (dp[i - 1] >= local_max - mid) {
                dp[i] = dp[i - 1];
                cnt[i] = cnt[i - 1];
            } else {
                dp[i] = local_max - mid;
                cnt[i] = local_max_cnt + 1;
            }

            if (local_max < dp[i - 1]) {
                local_max = dp[i - 1];
                local_max_cnt = cnt[i - 1];
            }
        }

        if (cnt[n] <= k) {
            r = mid;
            ans = max(ans, dp[n] + mid * cnt[n]);
        } else
            l = mid + 1;
    }

    cout << sm + ans;
    return 0;
}