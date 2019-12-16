#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[10000001];
ll dp_cw[10000001], dp_ccw[10000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k, l;
    cin >> n >> k >> l;
    FOR(i, 1, n + 1) { cin >> a[i]; }
    dp_cw[0] = dp_ccw[0] = 0;

    FOR(i, 1, n + 1) dp_cw[i] = 2 * a[i] + dp_cw[max(0, i - k)];
    for (int i = n; i > 0; i--) dp_ccw[i] = 2 * (l - a[i]) + dp_ccw[min(n + 1, i + k) % (n + 1)];

    ll ans = LLONG_MAX;
    FOR(i, 0, n + 1) ans = min(ans, dp_cw[i] + dp_ccw[(i + 1) % (n + 1)]);
    FOR(i, 0, n + 1 - k) ans = min(ans, dp_cw[i] + l + dp_ccw[(i + k + 1) % (n + 1)]);

    cout << ans << '\n';
    return 0;
}