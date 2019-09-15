#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = (1ll << 50) - 1;
ll n, s, e, a[2005], dt1[2005];
bool dt2[305][305];

bool can(ll V) {
    if (s == 1) {
        for (ll i = 1; i <= n; i++) {
            ll cur = 0;
            dt1[i] = inf;
            for (ll j = i - 1; j >= 0; j--) {
                cur += a[j + 1];
                if ((cur & V) == cur) {
                    dt1[i] = min(dt1[i], dt1[j] + 1);
                }
            }
        }
        return dt1[n] <= e;
    } else {
        dt2[0][0] = true;
        for (ll i = 1; i <= n; i++) {
            for (ll k = 1; k <= i; k++) {
                ll cur = 0;
                dt2[i][k] = false;
                for (ll j = i - 1; j >= 0; j--) {
                    cur += a[j + 1];
                    if ((cur & V) == cur) {
                        dt2[i][k] |= dt2[j][k - 1];
                    }
                }
                if (i == n && s <= k && k <= e && dt2[i][k]) return true;
            }
        }
        return false;
    }
}

int main() {
    cin >> n >> s >> e;
    for (ll i = 1; i <= n; i++) cin >> a[i];
    ll S = 0, E = inf;
    while (S < E) {
        ll M = (S + E) / 2;
        can(M) ? E = M : S = M + 1;
    }
    cout << S;
    return 0;
}