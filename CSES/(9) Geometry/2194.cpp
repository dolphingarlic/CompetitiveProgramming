#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
struct Point {
    ll x, y;
 
    ll dist(Point B) { return (B.x - x) * (B.x - x) + (B.y - y) * (B.y - y); }

    bool operator<(Point B) {
        if (x == B.x) return y < B.y;
        return x < B.x;
    }
} points[200001];
 
ll stripClosest(vector<Point> strip, ll d) {
    sort(strip.begin(), strip.end(), [](Point A, Point B) { return A.y < B.y; });
    for (int i = 0; i < strip.size(); i++)
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < d; j++)
            if (strip[i].dist(strip[j]) < d)
                d = strip[i].dist(strip[j]);
    return d;
}
 
ll closestPair(int l, int r) {
    if (r - l < 3) {
        ll dist = LLONG_MAX;
        for (int i = l; i < r; i++) for (int j = i + 1; j <= r; j++)
            dist = min(dist, points[i].dist(points[j]));
        return dist;
    }
 
    int mid = (l + r) / 2;
    ll ld = closestPair(l, mid), rd = closestPair(mid, r), d = min(ld, rd);
 
    vector<Point> strip;
    for (int i = l; i <= r; i++) if ((points[i].x - points[mid].x) * (points[i].x - points[mid].x) < d)
        strip.push_back(points[i]);
 
    return stripClosest(strip, d);
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> points[i].x >> points[i].y;
    sort(points + 1, points + n + 1);
    cout << closestPair(1, n);
    return 0;
}