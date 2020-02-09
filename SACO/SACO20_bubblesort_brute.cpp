#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[100001], n, q;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    FOR(i, 1, n + 1) cin >> a[i];

    ll ans = 0;
    FOR(i, 1, n + 1) FOR(j, 1, i) if (a[i] < a[j]) ans++;
    cout << ans << '\n';

    while (q--) {
        int x, y;
        cin >> x >> y;
        a[x + 1] = y;

        ans = 0;
        FOR(i, 1, n + 1) FOR(j, 1, i) if (a[i] < a[j]) ans++;
        cout << ans << '\n';
    }
    return 0;
}