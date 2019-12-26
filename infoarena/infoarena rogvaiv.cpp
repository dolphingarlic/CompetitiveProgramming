#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll dp[50001];
// dp[i] = (i-th drop is a random colour) + (the last 7 drops form a rainbow) -
// (double counted stuff when last 7 drops form a rainbow)
// We also need to handle double rainbows (i.e. 1234567654321 or 7654321234567)

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("rogvaiv.in", "r", stdin);
    freopen("rogvaiv.out", "w", stdout);

    ll c, n, m;
    cin >> c >> n >> m;
    if (c == 1) {
        ll s = 1;
        FOR(i, 7, n + 1) {
            dp[i] = (7 * dp[i - 1] + s - dp[i - 7] + m) % m;
            s = (s * 7) % m;
        }
        cout << dp[n];
    } else {
        ll s = 2;
        FOR(i, 7, n + 1) {
            dp[i] = (7 * dp[i - 1] + s - dp[i - 6] + 5 * dp[i - 7] + m) % m;
            s = (s * 7) % m;
        }
        cout << dp[n];
    }
    return 0;
}