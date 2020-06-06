/*
SACO 2008 Containment
- 
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[100000], idx[100000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    FOR(i, 0, m) cin >> a[i];
    sort(a, a + m);

    FOR(i, 0, m) idx[i] = lower_bound(a, a + m, (a[i] + k) % n) - a;

    int curr = 0, ans = 0, loop_cnt = 0;
    FOR(i, 0, m) curr = idx[curr];
    for (int i = curr; loop_cnt + (i >= curr) < 2; ans++) {
        if (idx[i] <= i) loop_cnt++;
        i = idx[i];
    }
    cout << ans;
    return 0;
}