#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[1000000], b[1000000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, n) cin >> a[i];
    FOR(i, 0, m) cin >> b[i];

    int ans = 0;
    FOR(i, 0, n) {
        int ptr = upper_bound(b, b + m, a[i]) - b;
        int dist = INT_MAX;
        if (ptr < m) dist = min(dist, b[ptr] - a[i]);
        if (ptr) dist = min(dist, a[i] - b[ptr - 1]);
        ans = max(ans, dist);
    }

    cout << ans;
    return 0;
}