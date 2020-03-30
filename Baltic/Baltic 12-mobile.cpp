/*
Baltic 2012 Mobile
- Binary search for the radius R
- If we draw circles with radius R on each transceiver, the radius is good
  iff each point on the highway is inside or on at least 1 circle
- Notice how we can draw segments denoting where the circles intersect the highway
  and then check that each point is covered by at least 1 segment
- We can do this in O(N) (Sorting with O(N log N) is too slow)
- Complexity: O(N log MAX_COORD)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
using namespace std;

pair<long long, long long> p[1000000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, len;
    cin >> n >> len;
    FOR(i, 0, n) cin >> p[i].x >> p[i].y;

    double l = 1, r = 5e8;
    while (r - l > 1e-3) {
        double mid = (l + r) / 2, curr = 0;
        FOR(i, 0, n) {
            double delta = sqrt(mid * mid - p[i].y * p[i].y);
            double a = p[i].x - delta, b = p[i].x + delta;
            if (a <= curr) curr = max(curr, b);
        }

        if (curr >= len) r = mid;
        else l = mid;
    }

    cout << fixed << setprecision(4) << l;
    return 0;
}