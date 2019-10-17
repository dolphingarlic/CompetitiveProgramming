#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int l[1000001], r[1000001], a[1000001];
ll ans = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    priority_queue<pair<int, int>> pq;
    FOR(i, 1, n + 1) {
        cin >> a[i];
        pq.push({-a[i], i});
        l[i] = i - 1, r[i] = i + 1;
    }

    while (pq.size() - 1) {
        int pos = pq.top().second;
        pq.pop();

        if (!l[pos]) {
            ans += a[r[pos]];
            l[r[pos]] = l[pos];
        } else if (r[pos] > n) {
            ans += a[l[pos]];
            r[l[pos]] = r[pos];
        } else {
            ans += min(a[r[pos]], a[l[pos]]);
            l[r[pos]] = l[pos];
            r[l[pos]] = r[pos];
        }
    }

    cout << ans;
    return 0;
}