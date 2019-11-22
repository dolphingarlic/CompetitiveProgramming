#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[100000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> a[i];
    sort(a, a + n);

    int lptr = 0, rptr = 0;
    ll ans = 0;
    for (; rptr < n; rptr++) {
        while (a[lptr] < a[rptr] * 0.9) lptr++;
        ans += rptr - lptr;
    }
    cout << ans;
    return 0;
}