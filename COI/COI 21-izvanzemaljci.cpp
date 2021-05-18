#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 3e9 - 4;

struct Point {
    ll x, y;
} points[100001];

struct Square {
    Point p;
    ll l;
};

int n, k;

pair<ll, vector<Square>> one() {
    // Bounding box
    ll mn_x = INT_MAX, mn_y = INT_MAX;
    ll mx_x = INT_MIN, mx_y = INT_MIN;
    for (int i = 1; i <= n; i++) {
        mn_x = min(mn_x, points[i].x);
        mx_x = max(mx_x, points[i].x);
        mn_y = min(mn_y, points[i].y);
        mx_y = max(mx_y, points[i].y);
    }
    ll l = max({1ll, mx_x - mn_x, mx_y - mn_y});
    return {l, {{{mn_x, mn_y}, l}, {{INF, INF}, 1}, {{INF + 2, INF + 2}, 1}}};
}

pair<ll, vector<Square>> two() {
    // Sweep line
    ll l_best = INT_MAX;
    Square s1_best, s2_best;

    multiset<ll> ys;
    for (int i = 1; i <= n; i++) ys.insert(points[i].y);
    sort(points + 1, points + n + 1,
         [](Point A, Point B) { return A.x < B.x; });
    ll mn_y = INT_MAX, mx_y = INT_MIN;
    for (int i = 1; i < n; i++) {
        mn_y = min(mn_y, points[i].y);
        mx_y = max(mx_y, points[i].y);
        ys.erase(ys.find(points[i].y));
        if (points[i].x == points[i + 1].x) continue;
        ll l = max({points[i].x - points[1].x, mx_y - mn_y,
                    points[n].x - points[i + 1].x, *ys.rbegin() - *ys.begin(),
                    1ll});
        if (l < l_best) {
            l_best = l;
            s1_best = {{points[i].x -
                            max({points[i].x - points[1].x, mx_y - mn_y, 1ll}),
                        mn_y},
                       max({points[i].x - points[1].x, mx_y - mn_y, 1ll})};
            s2_best = {{points[i + 1].x, *ys.begin()},
                       max({points[n].x - points[i + 1].x,
                            *ys.rbegin() - *ys.begin(), 1ll})};
        }
    }

    multiset<ll> xs;
    for (int i = 1; i <= n; i++) xs.insert(points[i].x);
    sort(points + 1, points + n + 1,
         [](Point A, Point B) { return A.y < B.y; });
    ll mn_x = INT_MAX, mx_x = INT_MIN;
    for (int i = 1; i < n; i++) {
        mn_x = min(mn_x, points[i].x);
        mx_x = max(mx_x, points[i].x);
        xs.erase(xs.find(points[i].x));
        if (points[i].y == points[i + 1].y) continue;
        ll l = max({points[i].y - points[1].y, mx_x - mn_x,
                    points[n].y - points[i + 1].y, *xs.rbegin() - *xs.begin(),
                    1ll});
        if (l < l_best) {
            l_best = l;
            s1_best = {{mn_x, points[i].y - max({points[i].y - points[1].y,
                                                 mx_x - mn_x, 1ll})},
                       max({points[i].y - points[1].y, mx_x - mn_x, 1ll})};
            s2_best = {{*xs.begin(), points[i + 1].y},
                       max({points[n].y - points[i + 1].y,
                            *xs.rbegin() - *xs.begin(), 1ll})};
        }
    }

    return {l_best, {s1_best, s2_best, {{INF, INF}, 1}}};
}

pair<ll, vector<Square>> three() {
    // Sweep line + greedy
    ll l_best = INT_MAX;
    Square s1_best, s2_best, s3_best;

    sort(points + 1, points + n + 1,
         [](Point A, Point B) { return A.x < B.x; });
    for (int i = 2; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            
        }

        sort(points + i + 1, points + n + 1,
             [](Point A, Point B) { return A.y < B.y; });
        for (int j = i + 1; j <= n; j++) {

        }
        sort(points + i + 1, points + n + 1,
             [](Point A, Point B) { return A.x < B.x; });
    }

    return {l_best, {s1_best, s2_best, s3_best}};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> points[i].x >> points[i].y;

    vector<pair<ll, vector<Square>>> ans;
    if (k >= 1) ans.push_back(one());
    if (k >= 2) ans.push_back(two());
    if (k >= 3) ans.push_back(three());
    sort(ans.begin(), ans.end(),
         [](pair<ll, vector<Square>> A, pair<ll, vector<Square>> B) {
             return A.first < B.first;
         });
    for (int i = 0; i < k; i++)
        cout << ans[0].second[i].p.x << ' ' << ans[0].second[i].p.y << ' '
             << ans[0].second[i].l << '\n';
    return 0;
}
