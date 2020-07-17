/*
LMIO 2019 Noras
- First, find the points where the ray from each star intersects the circle
    - We can simplify this and only care about the x-coordinates, since dx is constant
        - If the line is vertical, just rotate it 90 degrees
    - To find the x-coordinates, we solve for x in the equation
      (m^2 + 1)x^2 + 2mcx + c^2 - r^2 = 0
      where m and c are the variables in the line equation y = mx + c
- After finding these points, we know in which time interval each star will be visible
- Then just do a line sweep to find the time with the most visible stars
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    long double r;
    cin >> n >> r;
    vector<pair<long double, int>> stars;
    FOR(i, 0, n) {
        long double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) swap(x1, y1), swap(x2, y2);
        long double v = x2 - x1;

        long double m = (y1 - y2) / (x1 - x2);
        long double c = y1 - m * x1;
        if (m * m * c * c < (m * m + 1) * (c * c - r * r)) continue;

        long double int_1 =
            (-m * c + sqrt(m * m * c * c - (m * m + 1) * (c * c - r * r))) /
            (m * m + 1);
        long double int_2 =
            (-m * c - sqrt(m * m * c * c - (m * m + 1) * (c * c - r * r))) /
            (m * m + 1);
        if ((int_1 - x1) / v > (int_2 - x1) / v) swap(int_1, int_2);

        stars.push_back({ceil((int_1 - x1) / v), -1});
        stars.push_back({floor((int_2 - x1) / v), 1});
    }
    stars.push_back({0, 0});
    sort(stars.begin(), stars.end());

    int ans = 0, cnt = 0;
    for (pair<long double, int> i : stars) {
        cnt -= i.second;
        if (i.first >= 0) ans = max(ans, cnt);
    }
    cout << ans;
    return 0;
}