#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll d[100000], e[100000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, k;
    cin >> n >> k;
    FOR(i, 0, n) cin >> d[i];
    FOR(i, 0, n) {
        ll x;
        cin >> x;
        d[i] -= x;
    }
    sort(d, d + n);

    FOR(i, 0, n) e[i] = d[i];
    ll x = d[n / 2], y = d[(n - 1) / 2];
    FOR(i, 0, n) {
        d[i] -= x, e[i] -= y;
        d[i] = abs(d[i]), e[i] = abs(e[i]);
    }
    sort(d, d + n);
    sort(e, e + n);

    ll da = 0, ea = 0;
    FOR(i, 0, n - k) da += d[i], ea += e[i];
    cout << min(da, ea);
    return 0;
}