#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Point {
  ll x, y;
};

bool on_segment(Point p, Point q, Point r) {
  if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) &&
      q.y >= min(p.y, r.y))
    return true;
  return false;
}

int orientation(Point p, Point q, Point r) {
  ll cross = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  if (cross == 0) return 0;
  return (cross > 0) ? 1 : 2;
}

bool intersect(Point p1, Point q1, Point p2, Point q2) {
  int o1 = orientation(p1, q1, p2);
  int o2 = orientation(p1, q1, q2);
  int o3 = orientation(p2, q2, p1);
  int o4 = orientation(p2, q2, q1);

  if (o1 != o2 && o3 != o4) return true;
  if (!o1 && on_segment(p1, p2, q1)) return true;
  if (!o2 && on_segment(p1, q2, q1)) return true;
  if (!o3 && on_segment(p2, p1, q2)) return true;
  if (!o4 && on_segment(p2, q1, q2)) return true;
  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    Point a, b, c, d;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;

    if (intersect(a, b, c, d)) cout << "YES\n";
    else cout << "NO\n";
  }
  return 0;
}