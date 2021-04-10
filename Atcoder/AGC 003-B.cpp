#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll a[100001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i] / 2;
        if ((a[i] & 1) && a[i + 1]) {
            a[i + 1]--;
            ans++;
        }
    }
    cout << ans;
    return 0;
}
