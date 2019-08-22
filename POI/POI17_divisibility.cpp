#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

ll sum = 0, a[1000000], pref[1000001];
ll b, q;

ll bin_search(ll k) {
    ll l = 0, r = b;
    while (l != r) {
        ll mid = (l + r) / 2;
        if (pref[mid] < k) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> b >> q;
    FOR(i, 0, b) {
        cin >> a[i];
        sum = (sum + (a[i] * i) % (b - 1)) % (b - 1);
    }
    if (sum % (b - 1)) a[sum % (b - 1)]--;
    pref[0] = a[0];
    FOR(i, 1, b) {
        pref[i] = pref[i - 1] + a[i];
    }
    pref[b] = LLONG_MAX;

    FOR(i, 0, q) {
        ll x;
        cin >> x;
        ll pos = bin_search(x + 1);
        if (pos == b) cout << "-1\n";
        else cout << pos << '\n';
    }
    return 0;
}