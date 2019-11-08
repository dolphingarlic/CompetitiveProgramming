#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[40];

vector<ll> bitmask(int x, int y) {
    int r = y - x;
    vector<ll> ret;
    FOR(i, 0, (1 << r)) {
        ll sm = 0;
        FOR(j, 0, r) if (i & (1 << j)) sm += a[x + j];
        ret.push_back(sm);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll b;
    cin >> n >> b;
    FOR(i, 0, n) cin >> a[i];

    vector<ll> l = bitmask(0, n / 2), r = bitmask(n / 2, n);
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    ll ans = 0;
    for (ll i : l) {
        if (i > b) break;
        ans += upper_bound(r.begin(), r.end(), b - i) - r.begin();
    }
    cout << ans;
    return 0;
}