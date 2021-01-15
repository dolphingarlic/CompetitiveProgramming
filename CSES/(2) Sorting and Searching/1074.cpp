#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
ll a[200001];
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> a[i];
    sort(a, a + n);
    ll ans = 0;
    FOR(i, 0, n) ans += abs(a[i] - a[n / 2]);
    cout << ans;
    return 0;
}