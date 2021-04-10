#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    map<pair<int, int>, ll> twofive;
    for (int i = 0; i < n; i++) {
        double x;
        cin >> x;
        ll v = llround(x * 1e9);
        int two = 0, five = 0;
        while (v % 2 == 0) {
            v /= 2;
            two++;
        }
        while (v % 5 == 0) {
            v /= 5;
            five++;
        }
        twofive[{two, five}]++;
    }
    ll ans = 0;
    for (auto i : twofive) for (auto j : twofive) {
        if (i.first.first + j.first.first >= 18 && i.first.second + j.first.second >= 18) {
            if (i < j) ans += i.second * j.second;
            else if (i == j) ans += i.second * (i.second - 1) / 2;
        }
    }
    cout << ans;
    return 0;
}
