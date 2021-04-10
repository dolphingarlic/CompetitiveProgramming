#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll lozenge(ll n, ll m) {
    if (!n) return -m;
    return m / n * 2 * n + lozenge(m % n, n);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n, x;
    cin >> n >> x;
    if (x * 2 > n) x = n - x;
    cout << n + lozenge(x, n - x);
    return 0;
}
