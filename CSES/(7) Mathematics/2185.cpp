#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll a[20];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n;
    int k;
    cin >> n >> k;
    for (int i = 0; i < k; i++) cin >> a[i];
    ll ans = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        int mult = 1 - 2 * (__builtin_popcount(mask) & 1);
        ll tmp = n;
        for (int i = 0; i < k; i++) if (mask & (1 << i)) tmp /= a[i];
        ans += mult * tmp;
    }
    cout << abs(ans);
    return 0;
}
