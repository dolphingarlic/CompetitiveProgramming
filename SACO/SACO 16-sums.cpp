#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, m = (1ll << 60ll);
    cin >> n;
    int cnt = 0;
    FOR(i, 0, 64) if (n & (1ll << i)) cnt++, m = min(m, (1ll << i));
    if (cnt == 1) return cout << -1, 0;
    ll s = n / (m << 1) - m + 1, t = n / (m << 1) + m;
    if (s < 0) s = -s + 1;

    cout << s << ' ' << t;
    return 0;
}