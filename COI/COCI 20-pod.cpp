#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

pair<ll, int> a[1001];
ll ans[1001], sm = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) {
        ll v;
        cin >> v >> a[i].first;
        sm += v;
        a[i].second = i;
    }
    sort(a, a + n, greater<pair<ll, int>>());
    int i = 0;
    for (; sm; i++) {
        ans[a[i].second] = min(a[i].first, sm);
        sm -= min(a[i].first, sm);
    }
    cout << n - i << '\n';
    FOR(i, 0, n) cout << ans[i] << ' ';
    return 0;
}