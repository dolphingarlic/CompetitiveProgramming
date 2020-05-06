/*
Baltic 2009 Rect
- First, consider the N(N - 1) / 2 line segments formed by pairs of points
    - Let the "first point" of a segment be the point with smaller x-coordinate
(and y-coordinate)
- Notice how a rectangle is determined by a pair of parallel line segments of
  the same length and same y-intercept of the line perpendicular to their first
  points
- Next, notice how if we have a set of line segments sorted by x-coordinate such
  that they all have the same length, gradient, and y-intercept of the line
  perpendicular to their first points, the largest rectangle made from that set
  will use the first and last line segments
- This means we can sort the set of all line segments...
    - First by length
    - Then by gradient
    - Then by y-intercept of the line perpendicular to their first points
    - Then by x-coordinate
- Notice how this neatly partitions the set of line segments into our desired sets
- We can then simply use 2 pointers to find the starts and ends of each set
- Complexity: O(N^2 log N^2)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Point {
    ll x, y;
} points[1500];

ll sq_dist(ll dx, ll dy) { return dx * dx + dy * dy; }

bool same_grad(pair<Point, Point> A, pair<Point, Point> B) {
    return (A.first.y - A.second.y) * (B.first.x - B.second.x) ==
           (A.first.x - A.second.x) * (B.first.y - B.second.y);
}

bool less_grad(pair<Point, Point> A, pair<Point, Point> B) {
    if (A.first.x == A.second.x) return false;
    if (B.first.x == B.second.x) return true;
    return double(A.first.y - A.second.y) / (A.first.x - A.second.x) <
           double(B.first.y - B.second.y) / (B.first.x - B.second.x);
}

bool same_int(pair<Point, Point> A, pair<Point, Point> B) {
    return ((A.first.x * (A.first.x - A.second.x) +
             A.first.y * (A.first.y - A.second.y)) *
                (B.first.y - B.second.y) ==
            (B.first.x * (B.first.x - B.second.x) +
             B.first.y * (B.first.y - B.second.y)) *
                (A.first.y - A.second.y));
}

bool less_int(pair<Point, Point> A, pair<Point, Point> B) {
    if (A.first.x == A.second.x) return A.first.y < B.first.y;
    double A_m = double(A.first.y - A.second.y) / (A.first.x - A.second.x),
           B_m = double(B.first.y - B.second.y) / (B.first.x - B.second.x);
    return (A.first.y + A.first.x / A_m < B.first.y + B.first.x / B_m);
}

bool cmp(pair<Point, Point> A, pair<Point, Point> B) {
    ll A_len = sq_dist(A.first.x - A.second.x, A.first.y - A.second.y),
       B_len = sq_dist(B.first.x - B.second.x, B.first.y - B.second.y);
    if (A_len != B_len) return (A_len < B_len);
    if (!same_grad(A, B)) return less_grad(A, B);
    if (!same_int(A, B)) return less_int(A, B);
    return (A.first.x < B.first.x);
}

bool can_rect(pair<Point, Point> A, pair<Point, Point> B) {
    if ((A.first.x == A.second.x && A.first.y != B.first.y) ||
        (A.first.y == A.second.y && A.first.x != B.first.x))
        return false;
    ll A_len = sq_dist(A.first.x - A.second.x, A.first.y - A.second.y),
       B_len = sq_dist(B.first.x - B.second.x, B.first.y - B.second.y);
    return (A_len == B_len && same_grad(A, B) && same_int(A, B));
}

ll area(pair<Point, Point> A, pair<Point, Point> B) {
    return sqrt(sq_dist(A.first.x - A.second.x, A.first.y - A.second.y)) *
           sqrt(sq_dist(A.first.x - B.first.x, A.first.y - B.first.y));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> points[i].x >> points[i].y;
    vector<pair<Point, Point>> segs;
    FOR(i, 0, n) FOR(j, i + 1, n) {
        if (points[i].x < points[j].x ||
            (points[i].x == points[j].x && points[i].y < points[j].y))
            segs.push_back({points[i], points[j]});
        else
            segs.push_back({points[j], points[i]});
    }
    sort(segs.begin(), segs.end(), cmp);

    ll ans = 0;
    int ptr = 0;
    FOR(i, 0, segs.size()) {
        while (ptr != segs.size() - 1 && can_rect(segs[i], segs[ptr + 1]))
            ptr++;
        ans = max(ans, area(segs[i], segs[ptr]));
        i = ptr++;
    }
    cout << ans;
    return 0;
}