#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;
typedef long long ll;

struct Event {
    int x, y, id, type;
    bool operator<(Event b) {
        return x < b.x;
    }
};

int c[100001];
int find(int a) {
    while (c[a] != a) c[a] = c[c[a]], a = c[a];
    return a;
}
void onion(int a, int b) {
    c[find(a)] = c[find(b)];
}

Event events[200001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q, h;
    cin >> n >> q >> h;
    FOR(i, 1, n + 1) c[i] = i;
    FOR(i, 1, n + 1) {
        int x, y, l;
        cin >> x >> y >> l;
        events[2 * i - 1] = {x, y, i, 1};
        events[2 * i] = {x + l, y, i, 0};
    }
    sort(events + 1, events + 2 * n + 1);

    set<pair<int, int>> active; // y coord and id
    FOR(i, 1, 2 * n + 1) {
        int curr_x = events[i].x;
        vector<Event> to_process = {events[i]};
        while (i < 2 * n + 1 && events[i + 1].x == curr_x) {
            i++;
            to_process.push_back(events[i]);
        }

        vector<pair<int, int>> to_query;
        for (Event i : to_process) {
            // cout << i.x << ' ' << i.y << ' ' << i.id << ' ' << i.type << " $ ";
            if (i.type) {
                active.insert({i.y, i.id});
                to_query.push_back({i.y, i.id});
            } else active.erase({i.y, i.id});
        }
        // cout << '\n';

        // for (pair<int, int> i : active) cout << i.first << ' ' << i.second << " | ";
        // cout << '\n';

        for (pair<int, int> i : to_query) {
            auto pos = active.find(i);
            if (pos != active.begin() && i.first - (*prev(pos)).first <= h)
                onion(i.second, (*prev(pos)).second);
            if (pos != prev(active.end()) && (*next(pos)).first - i.first <= h)
                onion(i.second, (*next(pos)).second);
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        if (find(a) == find(b)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}