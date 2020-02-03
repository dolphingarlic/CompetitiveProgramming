#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[300001], h[300001], ans[1000001], cnt[1000001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    set<int> s;
    FOR(i, 0, n) {
        cin >> h[i];
        cnt[h[i]]++;
        s.insert(h[i]);
    }
    int m = 0;
    for (int i : s) a[m++] = i;

    FOR(i, 0, m) {
        if (a[i] <= k) continue;
        for (int j = k; j <= a[m - 1]; j += a[i]) ans[j] += cnt[a[i]] - (a[i] == j);
    }
    FOR(i, 0, n) cout << ans[h[i]] << ' ';
    return 0;
}