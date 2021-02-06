#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll MAXH;
ll bit1[100001], bit2[100001];
pair<ll, ll> a[100001];

void update(ll l, ll r, ll val) {
    for (ll i = l; i <= MAXH; i += (i & (-i))) bit1[i] += val;
    for (ll i = r + 1; i <= MAXH; i += (i & (-i))) bit1[i] -= val;

    for (ll i = l; i <= MAXH; i += (i & (-i))) bit2[i] += val * (l - 1);
    for (ll i = r + 1; i <= MAXH; i += (i & (-i)))  bit2[i] -= val * r;
}
ll query(ll l, ll r) {
    ll ans = 0;
    for (ll i = r; i; i -= (i & (-i))) ans += bit1[i] * r;
    for (ll i = l - 1; i; i -= (i & (-i))) ans -= bit1[i] * (l - 1);

    for (ll i = r; i; i -= (i & (-i))) ans -= bit2[i];
    for (ll i = l - 1; i; i -= (i & (-i))) ans += bit2[i];
    return ans;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    FOR(i, 0, n) cin >> a[i].first >> a[i].second;
    sort(a, a + n);
    MAXH = a[n - 1].first;

    ll ans = 0;
    FOR(i, 0, n) {
        ll ub = query(a[i].first - a[i].second + 1, a[i].first - a[i].second + 1);

        ll l = a[i].first - a[i].second + 1, r = a[i].first + 1;
        while (l != r) {
            ll mid = (l + r) / 2;
            if (query(mid, mid) < ub) r = mid;
            else l = mid + 1;
        }

        ll pos = l;
        ans += query(pos, a[i].first);
        update(pos, a[i].first, 1);

        l = 1, r = a[i].first;
        while (l != r) {
            ll mid = (l + r) / 2;
            if (query(mid, mid) > ub) l = mid + 1;
            else r = mid;
        }

        ans += query(l, l + a[i].second - a[i].first + pos - 2);
        update(l, l + a[i].second - a[i].first + pos - 2, 1);
    }

    cout << ans;
    return 0;
}
