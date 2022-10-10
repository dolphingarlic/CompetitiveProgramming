#include <iostream>
#include <vector>
#define int long long
#define nl "\n"
using namespace std;

int exe() {
    int ans = 0, n;
    cin >> n;
    vector<int> h(n);
    for (int& i : h) cin >> i;
    if (n == 1) return 0;
    for (int j : {1, 2}) {
        cout << h[0] << ' ';
        for (int i = 1; i < n - 1; i++) {
            if (h[i] > h[i - 1]) {
                int dif = h[i] - h[i - 1];
                ans += 2 * dif, h[i + 1] -= dif, h[i] = h[i - 1];
            }
            cout << h[i] << ' ';
        }
        cout << h[n - 1] << '\n';
        reverse(h.begin(), h.end());
    }
    return (h[n - 1] < 0 or h[n - 1] != h[n - 2] ? -1 : ans);
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(ios_base::failbit);
    int t;
    cin >> t;
    while (t--) cout << exe() << nl;
}
