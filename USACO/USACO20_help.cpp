#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

pair<ll, ll> a[64];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ifstream cin("help.in");
    ofstream cout("help.out");

    ll n, k;
    cin >> n >> k;
    FOR(i, 0, n) cin >> a[i].first >> a[i].second;

    ll ans = 0;
    FOR(i, 1, 1 << n) {
        vector<pair<ll, ll>> segs;
        FOR(j, 0, n) if (i & (1 << j)) {
            segs.push_back({a[j].first, 1});
            segs.push_back({a[j].second, -1});
        }
        sort(segs.begin(), segs.end());

        ll cnt = 0, gaps = 0;
        for (pair<ll, ll> j : segs) {
            cnt += j.second;
            if (!cnt) gaps++;
        }

        ll add = 1;
        FOR(j, 0, k) add = (add * gaps) % MOD;
        ans = (ans + add) % MOD;
    }
    cout << ans;
    return 0;
}