#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, t, pref[100001]{0};
    cin >> n >> t;
    FOR(i, 1, n + 1) {
        ll x;
        cin >> x;
        pref[i] = pref[i - 1] + x;
    }
    FOR(i, 0, t) {
        int x;
        cin >> x;
        ll mx = 0, mxindx = 0;
        FOR(j, 0, n - x + 2) {
            if (pref[j + x] - pref[j] > mx) {
                mx = pref[j + x] - pref[j];
                mxindx = j + 1;
            }
        }
        cout << mxindx << ' ' << mx << '\n';
    }
    return 0;
}