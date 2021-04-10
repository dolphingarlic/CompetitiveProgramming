#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll a[200000], b[200000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (a[i] + b[(i + n - 1) % n] + b[(i + 1) % n] <= b[i])
            q.push(i);
    }
    ll ans = 0;
    while (q.size()) {
        int i = q.front();
        q.pop();
        int j = (i + n - 1) % n, k = (i + 1) % n;

        ll moves = (b[i] - a[i]) / (b[j] + b[k]);
        ans += moves;
        b[i] -= moves * (b[j] + b[k]);

        if (a[j] + b[(j + n - 1) % n] + b[i] <= b[j])
            q.push(j);
        if (a[k] + b[i] + b[(k + 1) % n] <= b[k])
            q.push(k);
    }

    for (int i = 0; i < n; i++) if (a[i] != b[i]) return cout << -1, 0;
    cout << ans;
    return 0;
}
