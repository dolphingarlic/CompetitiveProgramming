#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll a[100000], mx = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    FOR(i, 0, n) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }

    ll l = mx, r = 1e18;
    while (l != r) {
        ll mid = (l + r) / 2;

        ll curr = 0, cnt = 1;
        FOR(i, 0, n) {
            if (curr + a[i] > mid) {
                curr = 0;
                cnt++;
            }
            curr += a[i];
        }

        if (cnt <= k) r = mid;
        else l = mid + 1;
    }

    cout << l;
    return 0;
}