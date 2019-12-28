#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
ll diffs[100001], a[100001];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, k;
    cin >> n >> k;
    FOR(i, 0, n) cin >> a[i];
    FOR(i, 0, n - 1) diffs[i] = a[i + 1] - a[i];
    sort(diffs, diffs + n - 1, greater<ll>());
    ll ans = a[n - 1] - a[0];
    FOR(i, 0, k - 1) ans -= diffs[i];
    cout << ans + k << '\n';
    return 0;
}