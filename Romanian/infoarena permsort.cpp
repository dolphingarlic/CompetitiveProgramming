#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n;
pair<int, int> a[1000001];
int bit[1000001];

void update(int pos) {
    for (; pos <= n; pos += (pos & (-pos))) bit[pos]++;
}
int query(int l, int r) {
    int ans = 0;
    for (; r; r -= (r & (-r))) ans += bit[r];
    for (l--; l > 0; l -= (l & (-l))) ans -= bit[l];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("permsort.in", "r", stdin);
    freopen("permsort.out", "w", stdout);
    
    cin >> n;
    FOR(i, 0, n) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    sort(a, a + n);
    ll ans = 0;
    int s = 1;
    FOR(i, 0, n) {
        if (a[i].second >= s) ans += a[i].second - s + 1 - query(s, a[i].second);
        else ans += n + a[i].second - s + 1 - query(1, a[i].second) - query(s, n);

        update(a[i].second);
        s = a[i].second + 1;
    }
    cout << ans;
    return 0;
}