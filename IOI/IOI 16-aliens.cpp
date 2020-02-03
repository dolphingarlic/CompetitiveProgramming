#include "aliens.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<int, int>
#define pli pair<ll, int>
#define x first
#define y second

const int mxN = 1e5;
int qh, qt, a[mxN], c[mxN];
ll b[mxN];
pii ps1[mxN];
vector<pii> ps2;

inline void al(int ai, ll bi, int ci) {
    while (qt - qh > 1 &&
           pli((b[qt - 1] - b[qt - 2]) * (a[qt - 1] - ai), c[qt - 1]) >
               pli((bi - b[qt - 1]) * (a[qt - 2] - a[qt - 1]), ci))
        --qt;
    a[qt] = ai, b[qt] = bi, c[qt] = ci;
    ++qt;
}

inline pli qry(ll xi) {
    while (qt - qh > 1 && pli(a[qh + 1] * xi + b[qh + 1], c[qh + 1]) <
                              pli(a[qh] * xi + b[qh], c[qh]))
        ++qh;
    return pli(a[qh] * xi + b[qh], c[qh]);
}

inline pli ddp(ll c) {
    qh = qt = 0;
    pli dp;
    for (int i = 0; i < ps2.size(); ++i) {
        ll d1 = max(i ? ps2[i - 1].x - ps2[i].y + 1 : 0, 0), d2 = ps2[i].y;
        al(-2 * d2, dp.x - d1 * d1 + d2 * d2, dp.y);
        d1 = ps2[i].x + 1;
        dp = qry(d1);
        dp.x += d1 * d1 + c, ++dp.y;
    }
    return dp;
}

ll take_photos(int n, int m, int k, vector<int> r, vector<int> c) {
    for (int i = 0; i < n; ++i) {
        ps1[i] = {r[i], c[i]};
        if (ps1[i].y > ps1[i].x) swap(ps1[i].y, ps1[i].x);
    }
    sort(ps1, ps1 + n);
    ps2.clear();
    for (int i = 0; i < n; ++i) {
        while (!ps2.empty() && ps1[i].y <= ps2.back().y) ps2.pop_back();
        ps2.push_back(ps1[i]);
    }
    ll lb = 0, rb = (ll)m * m, ans;
    while (lb <= rb) {
        ll mb = (lb + rb) / 2;
        pli dp = ddp(mb);
        if (dp.y <= k) {
            ans = dp.x;
            rb = mb - 1;
        } else
            lb = mb + 1;
    }
    return ans - lb * k;
}