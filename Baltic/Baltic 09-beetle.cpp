#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[301], l[301][301][2], r[301][301][2];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n + 1) cin >> a[i];
    a[n + 1] = 0;
    sort(a + 1, a + n + 2);
    int st = lower_bound(a + 1, a + n + 2, 0) - a;

    memset(l, 0x3f, sizeof(l));
    memset(r, 0x3f, sizeof(r));
    FOR(i, 1, st + 1) FOR(j, st, n + 2) l[i][j][0] = r[i][j][0] = 0;

    int ans = 0;
    FOR(k, 1, n + 1) {
        FOR(i, 1, st + 1) FOR(j, st, n + 2) {
            l[i][j][k & 1] = min(l[i - 1][j][1 - (k & 1)] + k * (a[i] - a[i - 1]), r[i][j + 1][1 - (k & 1)] + k * (a[j + 1] - a[i]));
            r[i][j][k & 1] = min(l[i - 1][j][1 - (k & 1)] + k * (a[j] - a[i - 1]), r[i][j + 1][1 - (k & 1)] + k * (a[j + 1] - a[j]));
        }
        ans = max(ans, k * m - l[st][st][k & 1]);
    }
    cout << ans;
    return 0;
}