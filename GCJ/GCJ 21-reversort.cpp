#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n, ans = 0;
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        for (int i = 0; i < n - 1; i++) {
            auto mn = min_element(v.begin() + i, v.end()) - v.begin();
            ans += mn - i + 1;
            reverse(v.begin() + i, v.begin() + mn + 1);
        }
        cout << "Case #" << tc << ": " << ans << '\n';
    }
    return 0;
}
