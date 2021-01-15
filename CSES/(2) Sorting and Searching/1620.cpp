#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
ll a[200001];
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    FOR(i, 0, n) cin >> a[i];
    ll l = 1, r = 1e18;
    while (l != r) {
        ll mid = (l + r) / 2, cnt = 0;
        FOR(i, 0, n) {
            cnt += mid / a[i];
            if (cnt >= k) break;
        }
        if (cnt < k) l = mid + 1;
        else r = mid;
    }
    cout << l;
    return 0;
}