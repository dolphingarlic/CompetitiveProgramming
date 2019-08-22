#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int a[500000];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> a[i];
    int mx = *max_element(a, a + n);
    int ans = 0;
    FOR(i, 0, n) ans += mx - a[i];
    cout << ans;
    return 0;
}