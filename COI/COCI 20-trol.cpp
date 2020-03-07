#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll d(ll n) {
    return 45 * (n / 9) + (n % 9) * (n % 9 + 1) / 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll q;
    cin >> q;
    while (q--) {
        ll a, b;
        cin >> a >> b;
        cout << d(b) - d(a - 1) << '\n';
    }
    return 0;
}