/*
JOI 2021 Snowballs
- Each snowball's size is bounded by its neighbours
- Run parallel binary search to find the earliest times that a snowball's "range"
  intersects with its neighbours' "ranges" (these two times may be different)
- These times give us the bounds, and therefore the final sizes, of the snowballs
- Complexity: O((N + Q) log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 1e18;

int n, q, l1[200002], r1[200002], l2[200002], r2[200002];
vector<int> check_mn[200002], check_mx[200002];
ll x[200002], w[200002], ans_mn[200002], ans_mx[200002];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
        l1[i] = l2[i] = 1;
        r1[i] = r2[i] = q;
    }
    x[0] = -INF, x[n + 1] = INF;
    for (int i = 1; i <= q; i++) cin >> w[i];
    for (int _ = 0; _ < 20; _++) {
        for (int i = 1; i <= n; i++) {
            int mid1 = (l1[i] + r1[i]) / 2;
            int mid2 = (l2[i] + r2[i]) / 2;
            check_mn[mid1].push_back(i);
            check_mx[mid2].push_back(i);
        }
        ll mn = 0, mx = 0, curr = 0;
        for (int i = 1; i <= q; i++) {
            curr += w[i];
            mn = min(mn, curr);
            mx = max(mx, curr);
            for (int j : check_mn[i]) {
                ll curr = x[j] + mn, to_left = x[j - 1] + mx;
                ans_mn[j] = max(ans_mn[j], x[j] - max(curr, to_left));
                if (curr <= to_left) r1[j] = i;
                else l1[j] = i + 1;
            }
            check_mn[i].clear();
            for (int j : check_mx[i]) {
                ll curr = x[j] + mx, to_right = x[j + 1] + mn;
                ans_mx[j] = max(ans_mx[j], min(curr, to_right) - x[j]);
                if (curr >= to_right) r2[j] = i;
                else l2[j] = i + 1;
            }
            check_mx[i].clear();
        }
    }
    for (int i = 1; i <= n; i++) cout << ans_mn[i] + ans_mx[i] << '\n';
    return 0;
}