#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 1e16;

struct Point { ll x, y; };

bool operator<(Point A, Point B) { return tie(A.x, A.y) < tie(B.x, B.y); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    vector<Point> ps;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        ps.push_back({x + y, x - y});
    }
    sort(ps.begin(), ps.end(), [](Point A, Point B) { return tie(A.y, A.x) < tie(B.y, B.x); });

    multiset<ll> best;
    for (int i = 0; i < k; i++) best.insert(INF);

    int lptr = 0;
    set<Point> active;
    for (Point p : ps) {
        ll to_beat = *best.rbegin();
        while (p.y - ps[lptr].y > to_beat) {
            active.erase(ps[lptr]);
            lptr++;
        }

        auto lb = active.lower_bound({p.x - to_beat, -INF});
        auto ub = active.upper_bound({p.x + to_beat, INF});
        for (auto ptr = lb; ptr != ub; ptr++)
            best.insert(max(abs(p.x - ptr->x), abs(p.y - ptr->y)));
        
        while (best.size() > k) best.erase(prev(best.end()));

        active.insert(p);
    }

    for (ll i : best) cout << i << '\n';
    return 0;
}