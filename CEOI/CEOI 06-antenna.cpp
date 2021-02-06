/*
CEOI 2006 Antenna
- Binary search on the answer
- For each possible radius, do a radial sweep centered on each point to check
  whether some circle with that radius can contain K points
    - The details are trig: see the code for them
- Complexity: O(N^2 log^2 N)
*/

#include <bits/stdc++.h>
#define x first
#define y second
typedef long double ld;
using namespace std;

const ld PI = 4 * atan(1);

int n, k;
pair<ld, ld> p[500], c, ans;

bool check(ld r) {
    for (int i = 0; i < n; i++) {
        vector<pair<ld, int>> events;
        for (int j = 0; j < n; j++) if (j != i) {
            ld dist = hypot(p[j].y - p[i].y, p[j].x - p[i].x);
            if (dist > 2 * r) continue;
            ld a = atan2(p[j].y - p[i].y, p[j].x - p[i].x);
            ld b = acos(dist / (2 * r));
            events.push_back({a - b, 1});
            events.push_back({a + b, -1});
            events.push_back({a - b + 2 * PI, 1});
            events.push_back({a + b + 2 * PI, -1});
        }
        sort(events.begin(), events.end());
        int cnt = 1;
        for (pair<ld, int> j : events) {
            cnt += j.second;
            if (cnt >= k) return c = {p[i].x + r * cos(j.first), p[i].y + r * sin(j.first)}, true;
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    ld l = 0, r = 6000;
    while (abs(r - l) > 1e-5) {
        ld mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    cout << fixed << setprecision(5) << l << '\n' << c.x << ' ' << c.y;
    return 0;
}
