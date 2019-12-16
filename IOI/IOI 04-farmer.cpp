#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll dp[150001];  // Maximum number of complete fields with exactly i trees
ll field[2001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll q, m, k, ans = 0, f = 0;
    cin >> q >> m >> k;

    fill(dp + 1, dp + q + 1, INT_MIN);
    FOR(i, 1, m + 1) {
        cin >> field[i];
    }
    sort(field + 1, field + m + 1);
    FOR(i, 1, m + 1) {
        for (int j = q; j >= field[i]; j--) {
            dp[j] = max(dp[j], dp[j - field[i]] + 1);
        }
    }
    
    for (int i = q; i > 0; i--) {
        if (dp[i] > 0) {
            ans = i, f = dp[i];
            q -= ans;
            break;
        }
    }

    if (f < m) ans += max(0ll, q - 1);
    else {
        FOR(i, 0, k) cin >> field[i];
        sort(field, field + k, greater<int>());
        int indx = 0;
        while (q) {
            ans += min(q, field[indx]) - 1;
            q -= min(q, field[indx++]);
        }
    }

    cout << ans << '\n';

    return 0;
}
