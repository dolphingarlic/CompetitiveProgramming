#include <iostream>
#include <algorithm>
typedef long long ll;
using namespace std;

ll a[50];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    ll ans = 0;
    while (*max_element(a, a + n) >= n) {
        auto mx = max_element(a, a + n);
        ll amt = *mx / n;
        for (int i = 0; i < n; i++) {
            if (i != mx - a) a[i] += amt;
            else a[i] -= amt * n;
        }
        ans += amt;
    }
    cout << ans;
}
