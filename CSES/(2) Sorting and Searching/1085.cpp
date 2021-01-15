#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
ll a[200001];
 
bool check(ll lim, int n, int k) {
    int cnt = 1;
    ll curr = 0;
    FOR(i, 0, n) {
        if (curr + a[i] > lim) {
            curr = a[i];
            cnt++;
        } else curr += a[i];
    }
    return cnt <= k;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    FOR(i, 0, n) cin >> a[i];
 
    ll l = *max_element(a, a + n), r = 1e15;
    while (l != r) {
        ll mid = (l + r) / 2;
        if (check(mid, n, k)) r = mid;
        else l = mid + 1;
    }
    cout << l;
    return 0;
}