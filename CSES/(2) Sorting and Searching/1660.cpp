#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
ll pref[200001];
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, x;
    cin >> n >> x;
    FOR(i, 1, n + 1) {
        int k;
        cin >> k;
        pref[i] = pref[i - 1] + k;
    }
    int ans = 0;
    FOR(i, 0, n) {
        ll ub = *prev(upper_bound(pref, pref + n + 1, x + pref[i]));
        ans += (ub == x + pref[i]);
    }
    cout << ans;
    return 0;
}