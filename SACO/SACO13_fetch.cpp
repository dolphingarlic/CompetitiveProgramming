#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[100000];

bool check(ll max_wait, ll n, ll t) {
    ll curr_start = a[0];
    FOR(i, 1, n) {
        if (a[i] - curr_start > max_wait) {
            if (a[i - 1] + t - a[i] > max_wait) return false;
            curr_start = a[i];
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, t;
    cin >> n >> t;
    FOR(i, 0, n) cin >> a[i];
    sort(a, a + n);

    ll l = 0, r = LLONG_MAX / 2;
    while (l != r) {
        ll mid = (l + r) / 2;
        if (check(mid, n, t)) r = mid;
        else l = mid + 1;
    }

    cout << l;
    return 0;
}