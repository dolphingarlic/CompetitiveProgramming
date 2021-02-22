/*
CEOI 2006 Walk
- (Btw this is Lebossle's code, since I don't like implementing stuff)
- Obviously, we're going to line sweep
- The editorial solution kinda sucks, so here's a better one:
- It's optimal to go to the right if you can, and only go up/down as much
  as you need to until you can go right again
- We can thus maintain a set of potential paths at some point in the sweep
- When we encounter a new rectangle, we insert its corners into the set
    - The distances to those corners is determined by the points in the
      set **between** them
    - After we calculate the minimum distance to those corners, we can
      simply erase the points between them from the set
- Since points are inserted and erased at most once and there are O(N)
  points, this is amortized O(N log N)
- We then use simple backtracking to reconstruct the answer
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

const ll INF = 1e13;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll x, y;
    cin >> x >> y;
    int n;
    cin >> n;
    vector<tuple<ll, ll, ll, ll>> rects;
    for (int i = 0; i < n; ++i) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x2 < x) rects.emplace_back(x1, y1, x2, y2);
    }
    rects.emplace_back(-1, -INF, -1, -1);
    rects.emplace_back(-1, 1, -1, INF);

    map<ll, pair<ll, ll>> cur;  // cur[y] = {x, dist}
    map<pair<ll, ll>, pair<ll, ll>> parent;
    cur[y] = {x, 0};
    sort(rects.begin(), rects.end(),
         [](auto t1, auto t2) { return get<2>(t1) > get<2>(t2); });
    for (auto t : rects) {
        ll x1, y1, x2, y2;
        tie(x1, y1, x2, y2) = t;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        ll y1d = INF, y2d = INF;
        pair<ll, ll> y1p, y2p;
        while (cur.lower_bound(y1) != cur.end()) {
            ll cx, cy, cd;
            auto aux = tie(cx, cd);
            tie(cy, aux) = *cur.lower_bound(y1);
            if (cy > y2) break;
            cur.erase(cur.lower_bound(y1));
            ll candY1d = cd + cy - (y1 - 1);
            ll candY2d = cd + (y2 + 1) - cy;
            if (candY1d < y1d) {
                y1d = candY1d;
                y1p = {cx, cy};
            }
            if (candY2d < y2d) {
                y2d = candY2d;
                y2p = {cx, cy};
            }
        }
        if (cur.count(y1 - 1) == 0 || cur[y1 - 1].second > y1d) {
            cur[y1 - 1] = {x2 + 1, y1d};
            parent[{x2 + 1, y1 - 1}] = y1p;
        }
        if (cur.count(y2 + 1) == 0 || cur[y2 + 1].second > y2d) {
            cur[y2 + 1] = {x2 + 1, y2d};
            parent[{x2 + 1, y2 + 1}] = y2p;
        }
    }

    cout << cur[0].second + x << endl;
    vector<pair<ll, ll>> ans;
    pair<ll, ll> p;
    while (p != make_pair(x, y)) {
        ans.emplace_back(0, parent[p].second - p.second);
        ans.emplace_back(parent[p].first - p.first, 0);
        p = parent[p];
    }
    if (ans.back() == make_pair(0LL, 0LL)) ans.pop_back();
    cout << ans.size() << endl;
    for (auto p : ans) cout << p.first << ' ' << p.second << '\n';
}