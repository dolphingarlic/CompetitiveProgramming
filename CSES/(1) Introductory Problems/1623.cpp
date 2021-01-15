#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;
 
int a[20];
ll tot = 0;
 
int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) {
        cin >> a[i];
        tot += a[i];
    }
 
    ll ans = INT_MAX;
    FOR(i, 0, 1<<n) {
        ll sm = 0;
        int temp = i;
        FOR(j, 0, n) {
            if (temp & 1) sm += a[j];
            temp >>= 1;
        }
        ans = min(ans, abs(tot - 2 * sm));
    }
 
    cout << ans << '\n';
    return 0;
}