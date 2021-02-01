/*
JOI 2018 Worst Reporter
- We can split IOI-chan and the contestants into contiguous groups that move together
  with a fixed period (i.e. after every P seconds, they move P spaces forward)
- The period of group i is at least double the period of group i-1, so there are O(log D) groups
- For each group, we can find the range that it covers after T seconds by just finding how
  many periods have passed and then shifting them that direction
- Complexity: O(Q log D)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Group {
    int l, r;
    ll period;
};

ll d[500001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<Group> groups = {{0, 0, 1}};
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
        ll p = groups.back().period;
        if (d[i] <= p) groups.back().l--;
        else groups.push_back({-i, -i, (d[i] + p - 1) / p * p});
    }
    while (q--) {
        ll l, r, t;
        cin >> t >> l >> r;
        int ans = 0;
        for (Group i : groups) {
            ll mv = t / i.period * i.period;
            ans += max(0ll, min(r, i.r + mv) - max(l, i.l + mv) + 1);
        }
        cout << ans << '\n';
    }
    return 0;
}