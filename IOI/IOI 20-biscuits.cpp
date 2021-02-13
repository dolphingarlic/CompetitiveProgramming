/*
IOI 2020 Packing Biscuits
- https://ioi2020.sg/wp-content/uploads/sites/4/2020/09/biscuits-solutions-ISC.pdf
*/

#include "biscuits.h"

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll x, s[60];
map<ll, ll> dp;

ll solve(ll n) {
    if (n <= 0) return 0;
    if (dp.count(n)) return dp[n];
    for (int i = 0; i < 60; i++) if ((1ll << i + 1) >= n)
        return dp[n] = solve(1ll << i) + solve(min(n, 1 + s[i] / x) - (1ll << i));
}

ll count_tastiness(ll x, vector<ll> a) {
    a.resize(60), ::x = x;
    s[0] = a[0];
    for (int i = 1; i < 60; i++) s[i] = s[i - 1] + (1ll << i) * a[i];
    dp.clear();
    dp[1] = 1;
    return solve(1ll << 60);
}
