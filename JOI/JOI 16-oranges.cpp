#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll a[20001], dp[20001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    ll k;
    cin >> n >> m >> k;
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ll mx = 0, mn = LLONG_MAX;
        for (int j = i; j > max(0, i - m); j--) {
            mx = max(mx, a[j]);
            mn = min(mn, a[j]);
            dp[i] = min(dp[i], dp[j - 1] + k + (i - j + 1) * (mx - mn));
        }
    }
    cout << dp[n] << '\n';
    return 0;
}