#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[101];
vector<pair<ll, ll>> le[101], ri[101];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, l, r, k, tot = 0; // Assume R = N
    cin >> n >> l >> r >> k;
    FOR(i, 0, n) {
        cin >> a[i];
        if (i > l - 2 && i < r) tot += a[i];
    }
    FOR(i, 0, 1 << (l - 1)) {
        ll dist = 0, save = 0, popcnt = 0;
        FOR(j, 0, l - 1) if (i & (1 << j)) {
            dist += j;
            save += a[j];
            popcnt++;
        }
        le[popcnt].push_back({dist, save});
    }
    FOR(i, 0, 1 << (n - l + 1)) {
        ll dist = 0, cost = 0, popcnt = 0;
        FOR(j, 0, n - l + 1) if (i & (1 << j)) {
            dist += j + l - 1;
            cost += a[j + l - 1];
            popcnt++;
        }
        ri[popcnt].push_back({dist, cost});
    }
    ll ans = 0;
    FOR(popcnt, 0, n) {
        for (pair<ll, ll> i : le[popcnt]) for (pair<ll, ll> j : ri[popcnt]) {
            if (j.first - i.first <= k) ans = min(ans, i.second - j.second);
        }
    }
    cout << tot + ans;
    return 0;
}