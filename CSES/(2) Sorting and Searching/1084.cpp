#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;
 
int a[200000], b[200000];
 
int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    FOR(i, 0, n) cin >> a[i];
    FOR(i, 0, m) cin >> b[i];
    sort(a, a + n);
    sort(b, b + m);
 
    int ans = 0, ptr = 0;
    for (int i = 0; i < n && ptr < m; i++) {
        // cout << a[i] << ' ' << b[ptr] << '\n';
        if (a[i] + k >= b[ptr] && a[i] - k <= b[ptr]) {
            ptr++;
            ans++;
        } else if (a[i] - k > b[ptr]) {
            ptr++;
            i--;
        }
    }
 
    cout << ans << '\n';
    return 0;
}