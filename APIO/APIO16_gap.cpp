#include <bits/stdc++.h>
#include "gap.h"
#define MAXN 1000000000000000000
using namespace std;
typedef long long ll;

ll a[100000], j = 0;

ll findGap(int T, int N) {
    if (T == 1) {
        ll l = 1, r = MAXN;
        ll mn, mx;
        vector<ll> v;
        for (ll i = 0; i < (N + 1) / 2; i++) {
            MinMax(l, r, &mn, &mx);
            a[j++] = mn;
            a[j++] = mx;
            l = mn + 1, r = mx - 1;
        }
        sort(a, a + N);
        ll ans = 0;
        for (ll i = 0; i < N - 1; i++) ans = max(ans, a[i + 1] - a[i]);
        return ans;
    } else {
        ll mn, mx;
        MinMax(1, MAXN, &mn, &mx);
        ll step = (mx - mn + N - 2) / (N - 1);
        ll ans = step, x, y, l = mn, i;
        for (i = mn; i + step < mx; i += step + 1) {
            MinMax(i, i + step, &x, &y);
            if (x != -1) {
                ans = max(ans, x - l);
                l = y;
            }
        }
        MinMax(i, mx, &x, &y);
        if (x != -1) ans = max(ans, x - l);
        return ans;
    }
}