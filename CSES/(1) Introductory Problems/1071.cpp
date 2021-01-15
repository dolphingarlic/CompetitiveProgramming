#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;
 
int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    FOR(i, 0, t) {
        ll x, y;
        cin >> x >> y;
        ll ans = max(x, y) * max(x, y);
        if (max(x, y) % 2 == 0) {
            if (max(x, y) == x) ans -= min(x, y) - 1;
            else ans -= 2 * y - x - 1;
        }
        else {
            if (max(x, y) == y) ans -= min(x, y) - 1;
            else ans -= 2 * x - y - 1;
        }
        cout << ans << '\n';
    }
    return 0;
}