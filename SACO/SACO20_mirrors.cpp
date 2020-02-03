// Ans = (edges on c-hull) - (c-hull edges on MST)

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
using namespace std;
typedef long long ll;

namespace big {
template <class T>
int sgn(T x) {
    return (x > 0) - (x < 0);
}
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); }  // makes dist()=1
    P perp() const { return P(-y, x); }        // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

typedef Point<ll> P;
typedef struct Quad* Q;
typedef __int128_t lll;       // (can be ll if coords are < 2e4)
P arb(LLONG_MAX, LLONG_MAX);  // not equal to any other point

#define sz(x) x.size()
#define all(x) x.begin(), x.end()

struct Quad {
    bool mark;
    Q o, rot;
    P p;
    P F() { return r()->p; }
    Q r() { return rot->rot; }
    Q prev() { return rot->o->rot; }
    Q next() { return r()->prev(); }
};

bool circ(P p, P a, P b, P c) {  // is p in the circumcircle?
    lll p2 = p.dist2(), A = a.dist2() - p2, B = b.dist2() - p2,
        C = c.dist2() - p2;
    return p.cross(a, b) * C + p.cross(b, c) * A + p.cross(c, a) * B > 0;
}
Q makeEdge(P orig, P dest) {
    Q q[] = {new Quad{0, 0, 0, orig}, new Quad{0, 0, 0, arb},
             new Quad{0, 0, 0, dest}, new Quad{0, 0, 0, arb}};
    FOR(i, 0, 4)
    q[i]->o = q[-i & 3], q[i]->rot = q[(i + 1) & 3];
    return *q;
}
void splice(Q a, Q b) {
    swap(a->o->rot->o, b->o->rot->o);
    swap(a->o, b->o);
}
Q connect(Q a, Q b) {
    Q q = makeEdge(a->F(), b->p);
    splice(q, a->next());
    splice(q->r(), b);
    return q;
}

pair<Q, Q> rec(const vector<P>& s) {
    if (sz(s) <= 3) {
        Q a = makeEdge(s[0], s[1]), b = makeEdge(s[1], s.back());
        if (sz(s) == 2) return {a, a->r()};
        splice(a->r(), b);
        auto side = s[0].cross(s[1], s[2]);
        Q c = side ? connect(b, a) : 0;
        return {side < 0 ? c->r() : a, side < 0 ? c : b->r()};
    }

#define H(e) e->F(), e->p
#define valid(e) (e->F().cross(H(base)) > 0)
    Q A, B, ra, rb;
    int half = sz(s) / 2;
    tie(ra, A) = rec({all(s) - half});
    tie(B, rb) = rec({sz(s) - half + all(s)});
    while ((B->p.cross(H(A)) < 0 && (A = A->next())) ||
           (A->p.cross(H(B)) > 0 && (B = B->r()->o)))
        ;
    Q base = connect(B->r(), A);
    if (A->p == ra->p) ra = base->r();
    if (B->p == rb->p) rb = base;

#define DEL(e, init, dir)                            \
    Q e = init->dir;                                 \
    if (valid(e))                                    \
        while (circ(e->dir->F(), H(base), e->F())) { \
            Q t = e->dir;                            \
            splice(e, e->prev());                    \
            splice(e->r(), e->r()->prev());          \
            e = t;                                   \
        }
    for (;;) {
        DEL(LC, base->r(), o);
        DEL(RC, base, prev());
        if (!valid(LC) && !valid(RC)) break;
        if (!valid(LC) || (valid(RC) && circ(H(RC), H(LC))))
            base = connect(RC, base->r());
        else
            base = connect(base->r(), LC->r());
    }
    return {ra, rb};
}

vector<P> triangulate(vector<P> pts) {
    sort(all(pts));
    assert(unique(all(pts)) == pts.end());
    if (sz(pts) < 2) return {};
    Q e = rec(pts).first;
    vector<Q> q = {e};
    int qi = 0;
    while (e->o->F().cross(e->F(), e->p) < 0) e = e->o;
#define ADD                      \
    {                            \
        Q c = e;                 \
        do {                     \
            c->mark = 1;         \
            pts.push_back(c->p); \
            q.push_back(c->r()); \
            c = c->next();       \
        } while (c != e);        \
    }
    ADD;
    pts.clear();
    while (qi < sz(q))
        if (!(e = q[qi++])->mark) ADD;
    return pts;
}

vector<P> convexHull(vector<P> pts) {
    if (sz(pts) <= 1) return pts;
    sort(all(pts));
    vector<P> h(sz(pts) + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(all(pts)))
        for (P p : pts) {
            while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) < 0) t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

int cmp[100001];
int find(int A) {
    while (cmp[A] != A) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}
void onion(int A, int B) { cmp[find(A)] = cmp[find(B)]; }

map<P, int> idx;
set<pair<P, P>> on_hull;

void solve(int n) {
    vector<P> pts(n);
    FOR(i, 0, n) {
        cin >> pts[i].x >> pts[i].y;
        idx[pts[i]] = cmp[i] = i;
    }
    vector<P> delaunay = triangulate(pts);
    vector<P> hull = convexHull(pts);

    int ans = hull.size();
    FOR(i, 1, ans) {
        on_hull.insert({hull[i], hull[i - 1]});
        on_hull.insert({hull[i - 1], hull[i]});
    }

    vector<pair<lll, pair<P, P>>> edges;
    for (int i = 0; i < delaunay.size(); i += 3) {
        edges.push_back({(delaunay[i] - delaunay[i + 1]).dist2(),
                         {delaunay[i], delaunay[i + 1]}});
        edges.push_back({(delaunay[i + 1] - delaunay[i + 2]).dist2(),
                         {delaunay[i + 1], delaunay[i + 2]}});
        edges.push_back({(delaunay[i + 2] - delaunay[i]).dist2(),
                         {delaunay[i + 2], delaunay[i]}});
    }

    sort(edges.begin(), edges.end());
    for (auto& i : edges) {
        if (find(idx[i.second.first]) != find(idx[i.second.second])) {
            onion(idx[i.second.first], idx[i.second.second]);
            if (on_hull.find(i.second) != on_hull.end()) ans--;
        }
    }

    cout << ans;
}
}  // namespace big

namespace small {
pair<ll, ll> points[1001];
pair<ll, pair<int, int>> lines[1000001];
bool on_hull[1001][1001];

ll sq(ll x) { return x * x; }

bool ccw(pair<ll, ll> A, pair<ll, ll> B, pair<ll, ll> C) {
    return (A.x - B.x) * (C.y - B.y) >= (A.y - B.y) * (C.x - B.x);
}

int cmp[1001];
int find(int A) {
    while (cmp[A] != A) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}
void onion(int A, int B) { cmp[find(A)] = cmp[find(B)]; }

void solve(int n) {
    FOR(i, 0, n) cin >> points[i].x >> points[i].y;
    sort(points, points + n);

    vector<pair<int, pair<ll, ll>>> upper;
    FOR(i, 0, n) {
        while (upper.size() > 1 &&
               ccw(points[i], upper.back().y, upper[upper.size() - 2].y))
            upper.pop_back();
        upper.push_back({i, points[i]});
    }
    upper.pop_back();
    vector<pair<int, pair<ll, ll>>> lower;
    for (int i = n - 1; ~i; i--) {
        while (lower.size() > 1 &&
               ccw(points[i], lower.back().y, lower[lower.size() - 2].y))
            lower.pop_back();
        lower.push_back({i, points[i]});
    }
    lower.pop_back();
    upper.insert(upper.end(), lower.begin(), lower.end());

    int ans = upper.size();
    FOR(i, 1, ans) {
        on_hull[upper[i].x][upper[i - 1].x] =
            on_hull[upper[i - 1].x][upper[i].x] = true;
    }
    on_hull[upper[0].x][upper[ans - 1].x] =
        on_hull[upper[ans - 1].x][upper[0].x] = true;

    int cnt = 0;
    FOR(i, 0, n) {
        cmp[i] = i;
        FOR(j, i + 1, n) {
            lines[cnt++] = {
                sq(points[i].x - points[j].x) + sq(points[i].y - points[j].y),
                {i, j}};
        }
    }
    sort(lines, lines + cnt);
    FOR(i, 0, cnt) {
        if (find(lines[i].y.x) != find(lines[i].y.y)) {
            onion(lines[i].y.x, lines[i].y.y);
            if (on_hull[lines[i].y.x][lines[i].y.y]) ans--;
        }
    }

    cout << ans;
}
}  // namespace small

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    if (n > 1000)
        big::solve(n);
    else
        small::solve(n);
    return 0;
}