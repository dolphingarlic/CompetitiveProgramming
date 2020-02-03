#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

pair<ll, ll> f[5001];
unordered_set<ll> flattened;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll R, C;
    cin >> R >> C;

    ll n;
    cin >> n;
    FOR(i, 0, n) cin >> f[i].first >> f[i].second;
    sort(f, f + n);
    FOR(i, 0, n) flattened.insert(f[i].first * 10000 + f[i].second);

    ll global = 0;
    FOR(i, 0, n) {
        FOR(j, i + 1, n) {
            ll ans = 0;
            ll cx = f[i].first, cy = f[i].second;
            ll dx = f[j].first - f[i].first, dy = f[j].second - f[i].second;

            if (cx - dx > 0 && cx - dx <= R && cy - dy > 0 && cy - dy <= C) continue;

            while (flattened.find(cx * 10000 + cy) != flattened.end()) {
                ans++;
                cx += dx, cy += dy;
            }
            
            if (cx > 0 && cx <= R && cy > 0 && cy <= C) continue;
            global = max(global, ans);
        }
    }

    if (global == 2) cout << 0;
    else cout << global;

    return 0;
}
