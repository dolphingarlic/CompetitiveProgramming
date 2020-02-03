#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Point {
    ll x, y, id;

    bool operator!=(Point b) { return b.x != x || b.y != y; }

    bool inside(Point a, Point b, Point c) {
        return (x - a.x) * (b.y - a.y) - (y - a.y) * (b.x - a.x) > 0 &&
               (c.x - a.x) * (y - a.y) - (c.y - a.y) * (x - a.x) > 0 &&
               (x - b.x) * (c.y - b.y) - (y - b.y) * (c.x - b.x) > 0 &&
               (a.x - b.x) * (y - b.y) - (a.y - b.y) * (x - b.x) > 0;
    }
};

vector<Point> filter(Point a, Point b, Point c, vector<Point> pset) {
    vector<Point> ret;
    for (Point i : pset) {
        if (i != a && i != b && i != c && i.inside(a, b, c)) ret.push_back(i);
    }
    return ret;
}

void solve(Point b1, Point b2, Point a, char colour, vector<Point> pset_r,
           vector<Point> pset_g, bool new_line = true) {
    if (new_line) cout << b1.id << ' ' << b2.id << ' ' << colour << '\n';

    vector<Point> filtered_r = filter(b1, b2, a, pset_r);
    vector<Point> filtered_g = filter(b1, b2, a, pset_g);

    if (filtered_r.size() && filtered_g.size()) {
        if (colour == 'r') {
            Point n = filtered_g[rand() % filtered_g.size()];
            solve(b1, b2, n, 'r', filtered_r, filtered_g, false);
            solve(a, n, b2, 'g', filtered_r, filtered_g);
            solve(n, a, b1, 'g', filtered_r, filtered_g, false);
        } else {
            Point n = filtered_r[rand() % filtered_r.size()];
            solve(b1, b2, n, 'g', filtered_r, filtered_g, false);
            solve(a, n, b2, 'r', filtered_r, filtered_g);
            solve(n, a, b1, 'r', filtered_r, filtered_g, false);
        }
    } else if (filtered_r.size()) {
        if (colour == 'r')
            for (Point i : filtered_r) cout << b1.id << ' ' << i.id << " r\n";
        else
            for (Point i : filtered_r) cout << a.id << ' ' << i.id << " r\n";
    } else if (filtered_g.size()) {
        if (colour == 'g')
            for (Point i : filtered_g) cout << b1.id << ' ' << i.id << " g\n";
        else
            for (Point i : filtered_g) cout << a.id << ' ' << i.id << " g\n";
    }
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);

    ll g;
    Point g1, g2;
    cin >> g >> g1.x >> g1.y >> g2.x >> g2.y;
    g1.id = 1, g2.id = 2;
    vector<Point> green;
    FOR(i, 2, g) {
        ll x, y;
        cin >> x >> y;
        green.push_back({x, y, i + 1});
    }
    ll r;
    Point r1, r2;
    cin >> r >> r1.x >> r1.y >> r2.x >> r2.y;
    r1.id = 1, r2.id = 2;
    vector<Point> red;
    FOR(i, 2, r) {
        ll x, y;
        cin >> x >> y;
        red.push_back({x, y, i + 1});
    }

    solve(g1, g2, r1, 'g', red, green);
    solve(r2, r1, g2, 'r', red, green);
    return 0;
}