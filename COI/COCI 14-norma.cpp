#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9;

pair<ll, ll> a[500001];
set<ll> low, high;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a, a + n);

    ll ans = 0;

    low.insert(-1); low.insert(n);
    FOR(i, 0, n) {
        auto ub = low.upper_bound(a[i].second);
        ans = (ans + a[i].first * ()) % MOD;
    }
    return 0;
}