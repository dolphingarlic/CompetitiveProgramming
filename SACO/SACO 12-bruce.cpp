/*
SACO 2012 Bruce
- Just do some maths to find the coordinates
- Complexity: O(1)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    ll s = ll(ceil(sqrt(t))) - 1;
    ll u = t - s * s;
    if (s & 1) {
        if (t > s * (s + 1)) {
            cout << s + 1 << ' ' << 2 * s + 2 - u;
        } else {
            cout << u << ' ' << s + 1;
        }
    } else {
        if (t > s * (s + 1)) {
            cout << 2 * s + 2 - u << ' ' << s + 1;
        } else {
            cout << s + 1 << ' ' << u;
        }
    }
    return 0;
}