// Ans = (edges on c-hull) - (c-hull edges on MST)

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
using namespace std;
typedef long long ll;

pair<ll, ll> points[1001];
pair<ll, pair<int, int>> lines[1000001];
bool on_hull[1001][1001];

ll sq(ll x) {
    return x * x;
}

bool ccw(pair<ll, ll> A, pair<ll, ll> B, pair<ll, ll> C) {
    return (A.x - B.x) * (C.y - B.y) >= (A.y - B.y) * (C.x - B.x);
}

int cmp[1001];
int find(int A) {
    while (cmp[A] != A) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}
void onion(int A, int B) {
    cmp[find(A)] = cmp[find(B)];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> points[i].x >> points[i].y;
    sort(points, points + n);

    // Convex hull
    vector<pair<int, pair<ll, ll>>> upper;
    FOR(i, 0, n) {
        while (upper.size() > 1 && ccw(points[i], upper.back().y, upper[upper.size() - 2].y)) upper.pop_back();
        upper.push_back({i, points[i]});
    }
    upper.pop_back();
    vector<pair<int, pair<ll, ll>>> lower;
    for (int i = n - 1; ~i; i--) {
        while (lower.size() > 1 && ccw(points[i], lower.back().y, lower[lower.size() - 2].y)) lower.pop_back();
        lower.push_back({i, points[i]});
    }
    lower.pop_back();
    upper.insert(upper.end(), lower.begin(), lower.end());

    int ans = upper.size();
    FOR(i, 1, ans) {
        on_hull[upper[i].x][upper[i - 1].x] = on_hull[upper[i - 1].x][upper[i].x] = true;
    }
    on_hull[upper[0].x][upper[ans - 1].x] = on_hull[upper[ans - 1].x][upper[0].x] = true;

    // MST
    int cnt = 0;
    FOR(i, 0, n) {
        cmp[i] = i;
        FOR(j, i + 1, n) {
            lines[cnt++] = {sq(points[i].x - points[j].x) + sq(points[i].y - points[j].y), {i, j}};
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
    return 0;
}