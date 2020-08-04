#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
typedef long long ll;
using namespace std;

const double PI = 4 * atan(1);

struct Event {
    short type, id;
    pair<ll, ll> loc;
};

pair<ll, ll> origin, polygon[22];
bool cmp(pair<ll, ll> a, pair<ll, ll> b) {
    return (a.x - origin.x) * (b.y - origin.y) < (a.y - origin.y) * (b.x - origin.x);
}
bool operator<(Event a, Event b) {
    double angle_a = atan2(a.loc.x - origin.x, a.loc.y - origin.y);
    double angle_b = atan2(b.loc.x - origin.x, b.loc.y - origin.y);
    if (angle_a < 0) angle_a += 2 * PI;
    if (angle_b < 0) angle_b += 2 * PI;

    if (angle_a == angle_b) return a.type > b.type;
    return angle_a < angle_b;
}

vector<Event> events, walls;
bool before[44444];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, r;
    cin >> n >> r >> origin.x >> origin.y;

    FOR(i, 0, r) {
        int m;
        cin >> m;
        FOR(j, 0, m) cin >> polygon[j].x >> polygon[j].y;
        sort(polygon, polygon + m, cmp);
        events.push_back({1, i, polygon[0]});
        events.push_back({-1, i, polygon[m - 1]});
    }
    sort(events.begin(), events.end());

    FOR(i, origin.x, n) walls.push_back({0, 0, {i, n}});
    FOR(i, 0, n) walls.push_back({0, 0, {n, n - i}});
    FOR(i, 0, n) walls.push_back({0, 0, {n - i, 0}});
    FOR(i, 0, n) walls.push_back({0, 0, {0, i}});
    FOR(i, 0, origin.x) walls.push_back({0, 0, {i, n}});

    int active = 0;
    for (Event i : events) {
        if (i.type == 1) before[i.id] = true;
        if (i.type == -1 && !before[i.id]) active++;
    }

    int ans = 0, ptr = 0;
    for (Event i : events) {
        while (ptr != 4 * n && walls[ptr] < i) {
            if (!active) ans++;
            ptr++;
        }
        
        if (i.type == 1) active++;
        else active--;
    }
    if (!active) ans += 4 * n - ptr;

    cout << ans;
    return 0;
}