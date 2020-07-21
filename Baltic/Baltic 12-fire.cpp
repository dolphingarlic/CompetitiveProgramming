/*
Baltic 2012 Fire
- Consider a fixed firework position at x = f_pos
- For any citizen (x, y), they fall in one of 8 cases (choose the minimum):
    - Distance =
        1: y
        2: y + S - f_pos + x
        3: f_pos - x
        4: f_pos - x + S - y
        5: x - f_pos
        6: x - f_pos + S - y
        7: y + S - x + f_pos
        8: y
- Notice how these functions are all linear, so the sum of the functions over
  all f_pos will be piecewise linear
    - This means we only care about the salient points i.e. points where a
      citizen changes cases
- Each citizen changes cases either 3 or 5 times depending on their y position
- This means there are O(N) "events"
- Thus we can just sort them and line sweep
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Event {
    ll pos;
    int idx, prv, curr;

    bool operator<(Event B) {
        if (pos == B.pos) return idx < B.idx;
        return pos < B.pos;
    }
};

struct Region {
    int cnt;
    ll x_sm, y_sm;
} regions[8];

int n;
ll s, x[100000], y[100000];
vector<Event> events;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> s;
    FOR(i, 0, n) {
        cin >> y[i] >> x[i];
        y[i] = abs(y[i]);
        regions[7].cnt++;
        regions[7].x_sm += x[i];
        regions[7].y_sm += y[i];
        if (y[i] > s) {
            events.push_back({x[i] - y[i], i, 7, 4});
            events.push_back({x[i], i, 4, 2});
            events.push_back({x[i] + y[i], i, 2, 0});
        } else {
            events.push_back({x[i] - s, i, 7, 6});
            events.push_back({x[i] - y[i], i, 6, 5});
            events.push_back({x[i], i, 5, 3});
            events.push_back({x[i] + y[i], i, 3, 1});
            events.push_back({x[i] + s, i, 1, 0});
        }
    }
    sort(events.begin(), events.end());

    ll ans = regions[7].y_sm;
    for (Event i : events) {
        regions[i.prv].cnt--;
        regions[i.prv].x_sm -= x[i.idx];
        regions[i.prv].y_sm -= y[i.idx];
        regions[i.curr].cnt++;
        regions[i.curr].x_sm += x[i.idx];
        regions[i.curr].y_sm += y[i.idx];

        ll dist = 
            regions[0].y_sm
            + regions[1].y_sm + regions[1].cnt * s - (regions[1].cnt * i.pos - regions[1].x_sm)
            + regions[2].cnt * i.pos - regions[2].x_sm
            + regions[3].cnt * i.pos - regions[3].x_sm + regions[3].cnt * s - regions[3].y_sm
            + regions[4].x_sm - regions[4].cnt * i.pos
            + regions[5].x_sm - regions[5].cnt * i.pos + regions[5].cnt * s - regions[5].y_sm
            + regions[6].y_sm + regions[6].cnt * s - (regions[6].x_sm - regions[6].cnt * i.pos)
            + regions[7].y_sm;
        ans = min(ans, dist);
    }
    cout << ans;
    return 0;
}