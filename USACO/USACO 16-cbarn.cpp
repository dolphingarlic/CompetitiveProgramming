/*
USACO 2016 Circular Barn
- It's much easier to solve this problem on a linear array, so try each "cut"
  of the circular array to turn it into a linear one
- Let dp[i][k] = The minimum distance the cows need to walk if we have k
                 open doors and we're only considering the prefix of length i
               = min(dp[j][k - 1] + sum(a[i] * i) - j * sum(a[i]))
- Notice how this looks awfully like CHT/D&C (since it's just some linear equations)
- We can thus solve it in either O(N^2 K) or O(N^2 K log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll dp[1001][8], pref[1001], prod_pref[1001];

void divide_conquer(int l, int r, int k, int l_opt, int r_opt) {
    int mid = (l + r) / 2, opt = -1;
    for (int i = l_opt; i <= r_opt; i++) {
        ll cost = (prod_pref[mid - 1] - prod_pref[i]) - i * (pref[mid - 1] - pref[i]);
        if (dp[mid][k] > dp[i][k - 1] + cost) {
            dp[mid][k] = dp[i][k - 1] + cost;
            opt = i;
        }
    }
    if (l != r) {
        divide_conquer(l, mid, k, l_opt, opt);
        divide_conquer(mid + 1, r, k, opt, r_opt);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("cbarn.in");
    ofstream cout("cbarn.out");
    int n, k;
    cin >> n >> k;
    deque<int> r(n);
    for (int i = 0; i < n; i++) cin >> r[i];
    ll ans = LLONG_MAX;
    for (int _ = 0; _ < n; _++) {
        memset(dp, 0x3f, sizeof dp);
        dp[0][0] = 0;
        for (int i = 0; i < n; i++) {
            pref[i] = r[i];
            prod_pref[i] = i * r[i];
            if (i) {
                pref[i] += pref[i - 1];
                prod_pref[i] += prod_pref[i - 1];
            }
        }
        for (int i = 1; i <= k; i++) divide_conquer(i, n, i, 0, n - 1);
        ans = min(ans, dp[n][k]);
        r.push_back(r.front());
        r.pop_front();
    }
    cout << ans << '\n';
    return 0;
}