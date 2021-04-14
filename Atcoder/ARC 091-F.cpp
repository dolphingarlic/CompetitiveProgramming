#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    ll nimber = 0;
    while (n--) {
        ll a, k;
        cin >> a >> k;
        while (a % k) {
            ll d = a / k;
            ll l = 0, r = INT_MAX;
            while (l != r) {
                ll mid = (l + r) / 2;
                if (a - mid * (d + 1) <= d * k) r = mid;
                else l = mid + 1;
            }
            a -= l * (d + 1);
        }
        nimber ^= a / k;
    }
    cout << (nimber ? "Takahashi" : "Aoki");
    return 0;
}
