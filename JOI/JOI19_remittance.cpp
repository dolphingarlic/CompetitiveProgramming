#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[1000000], b[1000000];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    FOR(i, 0, n) cin >> a[i] >> b[i];

    bool possible = true;
    while (possible) {
        possible = false;
        FOR(i, 0, n) {
            if (a[i] - b[i] > 1) {
                a[(i + 1) % n] += (a[i] - b[i]) / 2;
                a[i] -= (a[i] - b[i]) / 2 * 2;
            }
        }
        FOR(i, 0, n) possible |= (a[i] - b[i] > 1);
    }

    bool ans = true;
    FOR(i, 0, n) ans &= (a[i] == b[i]);

    if (ans) cout << "Yes";
    else cout << "No";
    return 0;
}