/*
POI 2009 Island
- If we can go from island A to B or A to C and C > B, then it's optimal to go from A to C
    - This is because the island is convex
- This means that for each town, we can go from N down to 1 and take the first available path
    - Since M paths are blocked, we skip over at most M paths
- Notice how the optimal route is convex
- Also, since we process paths in clockwise order, we can use a deque to find the optimal route
    - This is just a half-plane intersection
    - Similar to BkOI 2011 2circles
- After we find the optimal route, we easily find the distance
- Complexity: O(N + M)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Point {
    double x, y;
} p[100000], hull[100000];

int t = 0;

bool ccw(Point A, Point B, Point C) {
    return (A.x - B.x) * (C.y - B.y) <= (A.y - B.y) * (C.x - B.x);
}

Point intersect(Point A, Point B, Point C, Point D) {
    if (A.x == B.x) {
        return {A.x, (D.y - C.y) / (D.x - C.x) * A.x +
                         (C.y - (D.y - C.y) / (D.x - C.x) * C.x)};
    } else if (C.x == D.x) {
        return {C.x, (B.y - A.y) / (B.x - A.x) * C.x +
                         (A.y - (B.y - A.y) / (B.x - A.x) * A.x)};
    } else {
        return {
            ((A.y - (B.y - A.y) / (B.x - A.x) * A.x) -
             (C.y - (D.y - C.y) / (D.x - C.x) * C.x)) /
                ((D.y - C.y) / (D.x - C.x) - (B.y - A.y) / (B.x - A.x)),
            (B.y - A.y) / (B.x - A.x) *
                    (((A.y - (B.y - A.y) / (B.x - A.x) * A.x) -
                      (C.y - (D.y - C.y) / (D.x - C.x) * C.x)) /
                     ((D.y - C.y) / (D.x - C.x) - (B.y - A.y) / (B.x - A.x))) +
                (A.y - (B.y - A.y) / (B.x - A.x) * A.x)};
    }
}

void add_line(Point A, Point B) {
    if (!t) {
        hull[++t] = A;
        hull[++t] = B;
        return;
    }

    if (ccw(A, B, hull[t])) {
        while (t && ccw(A, B, hull[t])) t--;
        hull[t + 1] = intersect(hull[t], hull[t + 1], A, B);
        t++;
    }
    hull[++t] = B;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n + 1) cin >> p[i].x >> p[i].y;
    unordered_set<int> bad;
    while (m--) {
        int u, v;
        cin >> u >> v;
        bad.insert(u * n + v);
    }

    int prv = 1;
    FOR(i, 1, n) {
        for (int j = n; j > prv; j--) {
            if (bad.find(i * n + j) == bad.end()) {
                add_line(p[i], p[j]);
                prv = j;
                break;
            }
        }
    }

    double ans = 0;
    FOR(i, 1, t) ans += hypot(hull[i + 1].x - hull[i].x, hull[i + 1].y - hull[i].y);
    cout << fixed << setprecision(6) << ans;
    return 0;
}