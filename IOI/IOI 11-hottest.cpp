#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

ll pref[1000001];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    ll n, k;
    cin >> n >> k;
    FOR(i, 1, n + 1) {
        ll x;
        cin >> x;
        pref[i] = pref[i - 1] + x;
    }

    ll ans = 0;
    FOR(i, k, n + 1) {
        ans = max(ans, pref[i] - pref[i - k]);
    }
    cout << ans << '\n';
    return 0;
}