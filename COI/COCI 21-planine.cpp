#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Point {
    ll x, y;

    bool ccw(Point B, Point C) {
        return (x - B.x) * (C.y - B.y) >= (y - B.y) * (C.x - B.x);
    }
} p[1000000];

pair<long double, long double> seg[500000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    ll h;
    cin >> n >> h;
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;

    vector<int> stck;
    for (int i = 0; i < n; i++) {
        while (stck.size() > 1 && p[i].ccw(p[stck.back()], p[stck[stck.size() - 2]]))
            stck.pop_back();
        if (i && i < n - 1 && i % 2 == 0) {
            long double m = (long double)(p[i].x - p[stck.back()].x) / (long double)(p[i].y - p[stck.back()].y);
            long double c = p[i].x - m * p[i].y;
            seg[i / 2].first = m * h + c;
        }
        stck.push_back(i);
    }
    stck.clear();
    for (int i = n - 1; ~i; i--) {
        while (stck.size() > 1 && !p[i].ccw(p[stck.back()], p[stck[stck.size() - 2]]))
            stck.pop_back();
        if (i && i < n - 1 && i % 2 == 0) {
            long double m = (long double)(p[i].x - p[stck.back()].x) / (long double)(p[i].y - p[stck.back()].y);
            long double c = p[i].x - m * p[i].y;
            seg[i / 2].second = m * h + c;
        }
        stck.push_back(i);
    }

    n >>= 1; // There are now n - 1 segments
    sort(seg + 1, seg + n, [](pair<long double, long double> A, pair<long double, long double> B) { return A.second < B.second; });
    int cnt = 0;
    long double rightmost = -1e18;
    for (int i = 1; i < n; i++)
        if (seg[i].first > rightmost) cnt++, rightmost = seg[i].second;
    cout << cnt;
    return 0;
}