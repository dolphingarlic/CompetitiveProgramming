#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int a[100000];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, m) cin >> a[i];

    int lptr = 0, rptr = 0, curr = a[0];
    for (; rptr < m; curr += a[++rptr]) {
        while (curr > n) curr -= a[lptr++];
        if (curr == n) return cout << lptr + 1 << ' ' << rptr + 1, 0;
    }
    cout << "IMPOSSIBLE";
    return 0;
}