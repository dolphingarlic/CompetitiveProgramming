#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define x first
#define y second
typedef long long ll;
using namespace std;

const double PI = 4 * atan(1);

pair<ll, ll> v[400000];

bool cmp(pair<ll, ll> a, pair<ll, ll> b) {
    double angle_a = atan2(a.x, a.y), angle_b = atan2(b.x, b.y);
    if (angle_a < 0) angle_a += 2 * PI;
    if (angle_b < 0) angle_b += 2 * PI;
    return angle_a < angle_b;
}

pair<ll, ll> operator+(pair<ll, ll> a, pair<ll, ll> b) {
    return {a.x + b.x, a.y + b.y};
}
pair<ll, ll> operator-(pair<ll, ll> a, pair<ll, ll> b) {
    return {a.x - b.x, a.y - b.y};
}
ll operator*(pair<ll, ll> a, pair<ll, ll> b) { return a.x * b.y - a.y * b.x; }
ll d(pair<ll, ll> a) { return a.x * a.x + a.y * a.y; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    FOR(i, 0, n) cin >> v[i].x >> v[i].y;
    sort(v, v + n, cmp);
    FOR(i, 0, n) v[i + n] = v[i];

    pair<ll, ll> g_max = {0, 0}, l_max = {0, 0};
    queue<pair<pair<ll, ll>, ll>> active;
    FOR(i, 0, 2 * n) {
        while (active.size() && (active.front().first * v[i] > 0 ||
                                 i - active.front().second == n ||
                                 d(l_max - active.front().first) >= d(l_max))) {
            l_max = l_max - active.front().first;
            active.pop();
            if (d(l_max) > d(g_max)) g_max = l_max;
        }
        l_max = l_max + v[i];
        active.push({v[i], i});
        if (d(l_max) > d(g_max)) g_max = l_max;
    }

    cout << d(g_max) << '\n';
    return 0;
}
