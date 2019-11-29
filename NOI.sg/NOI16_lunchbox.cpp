#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[60000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m, n;
    cin >> m >> n;
    FOR(i, 0, n) cin >> a[i];
    sort(a, a + n);

    int cnt = 0;
    while (cnt != n && m >= a[cnt]) m -= a[cnt++];
    cout << cnt;
    return 0;
}