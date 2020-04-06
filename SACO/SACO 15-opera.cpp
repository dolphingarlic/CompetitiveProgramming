#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    priority_queue<pair<ll, ll>> pq;
    FOR(i, 0, n) {
        ll a, b;
        cin >> a >> b;
        pq.push({b, a});
    }

    ll mxh = 0;
    ll ans = 0;
    while (pq.size()) {
        ll p, h;
        tie(p, h) = pq.top();
        pq.pop();

        ans += max(0ll, h - mxh) * p;
        mxh = max(mxh, h);
    }
    cout << ans;
    return 0;
}