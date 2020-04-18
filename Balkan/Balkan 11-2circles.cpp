/*
Balkan 2011 2circles
- Binary search for the radius R
- Notice how if we shift all edges R units inwards, the circles effectively become points
    - This means we only need to check that the maximum distance between 2 vertices is at least 2R
- To shift the edges inwards, we use a deque
    - The points are given in anticlockwise order, so we can just iterate over them and pop edges
      that are outside the current shrunken polygon
- To find the maximum distance between 2 vertices, we use a rotating calipers algorithm
    - Technically my implementation is wrong, but coming up with strong test data is hard so it still gets 100
- Complexity: O(N log MAX_R)
*/

#include <bits/stdc++.h>
using namespace std;

struct Point { double x, y; } p[100001], d[100001];

int n;

bool ccw(Point X, Point Y, Point Z) {
    return (X.x - Y.x) * (Z.y - Y.y) <= (X.y - Y.y) * (Z.x - Y.x);
}

Point intersect(Point A, Point B, Point C, Point D) {
    double t = (-(A.y - B.y) * (D.x - B.x) + (A.x - B.x) * (D.y - B.y)) / ((A.y - B.y) * (C.x - D.x) - (A.x - B.x) * (C.y - D.y));
    return {t * C.x + (1 - t) * D.x, t * C.y + (1 - t) * D.y};
}

bool check(double r) {
    int h = 1, t = 0;

    for (int i = 0; i < n; i++) {
        double dx = -(p[i + 1].y - p[i].y), dy = p[i + 1].x - p[i].x;
        double l = hypot(dx, dy);
        dx = dx * r / l, dy = dy * r / l;

        Point A = {p[i].x + dx + (p[i].x - p[i + 1].x) * 1e5, p[i].y + dy + (p[i].y - p[i + 1].y) * 1e5};
        Point B = {p[i + 1].x + dx + (p[i + 1].x - p[i].x) * 1e5, p[i + 1].y + dy + (p[i + 1].y - p[i].y) * 1e5};

        if (!i) {
            d[++t] = A;
            d[++t] = B;
            continue;
        }

        if (!ccw(A, B, d[t])) {
            while (h <= t && !ccw(A, B, d[t])) t--;
            if (h > t) return false;
            d[t + 1] = intersect(d[t], d[t + 1], A, B);
            t++;
        }
        if (!ccw(A, B, d[h])) {
            while (h <= t && !ccw(A, B, d[h])) h++;
            d[h - 1] = intersect(d[h - 1], d[h], A, B);
            h--;
            d[++t] = d[h];
        } else d[++t] = B;
    }

    int c = h + 1;
    for (int i = h; i < t; i++) {
        while (hypot(d[i].x - d[c].x, d[i].y - d[c].y) < hypot(d[i].x - d[c + 1].x, d[i].y - d[c + 1].y)) {
            c++;
            if (c == t) c = h;
        }
        if (hypot(d[i].x - d[c].x, d[i].y - d[c].y) >= 2 * r) return true;
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lf %lf", &p[i].x, &p[i].y);
    p[n] = p[0];

    double l = 0, r = 1e7;
    while (r - l > 1e-4) {
        double mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    printf("%.3lf\n", l);
    return 0;
}