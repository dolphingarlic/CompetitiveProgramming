/*
JOI 2020 Neckties
- To minimize oddity, sort both arrays and pair employees and ties up in increasing order
- Maintain prefix and suffix maximums of oddity to account for one of the ties being taken away
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

pair<int, int> a[200002];
int b[200001], ans[200002], pref[200002], suff[200002];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 2) {
        cin >> a[i].first;
        a[i].second = i;
    }
    FOR(i, 1, n + 1) cin >> b[i];
    sort(a + 1, a + n + 2);
    sort(b + 1, b + n + 1);

    FOR(i, 1, n + 1) pref[i] = max(pref[i - 1], max(a[i].first - b[i], 0));
    FOR(i, 1, n + 1) suff[i] = max(suff[i - 1], max(a[n + 2 - i].first - b[n + 1 - i], 0));

    FOR(i, 1, n + 2) ans[a[i].second] = max(pref[i - 1], suff[n + 1 - i]);
    FOR(i, 1, n + 2) cout << ans[i] << ' ';
    return 0;
}