#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Edge {
    int a, b, c;
};

bool operator<(Edge x, Edge y) {
    if (x.a == y.a) {
        if (x.b == y.b) return x.c < y.c;
        return x.b < y.b;
    }
    return x.a < y.a;
}

Edge edges[200001];
int colour[200001];

bool is_tri(int n) {
    FOR(i, 1, n) {
        if (edges[i].a == edges[i - 1].a && edges[i].b == edges[i - 1].b) return false;
    }
    vector<pair<pair<int, int>, int>> events;
    FOR(i, 0, n) {
        events.push_back({{edges[i].a, 1}, -edges[i].b});
        events.push_back({{edges[i].b, -1}, edges[i].a});
    }
    sort(events.begin(), events.end());

    set<pair<int, int>> active;
    for (auto& i : events) {
        if (i.first.second == -1) {
            active.erase({i.first.first, i.second});
        } else {
            if (active.size() && -i.second > (*active.rbegin()).first) return false;
            active.insert({-i.second, i.first.first});
        }
    }
    return true;
}

bool is_patriotic(int n) {
    if (n <= 2000) {
        vector<Edge> all;
        set<Edge> has;
        FOR(i, 0, n) {
            if (i == n - 1) {
                all.push_back({1, n, colour[i]});
                has.insert({1, n, colour[i]});
            } else {
                all.push_back({i + 1, i + 2, colour[i]});
                has.insert({i + 1, i + 2, colour[i]});
            }
        }
        FOR(i, 0, n - 3) {
            all.push_back(edges[i]);
            has.insert(edges[i]);
        }

        int cnt = 0;
        FOR(i, 0, 2 * n - 3) FOR(j, i + 1, 2 * n - 3) {
            map<int, int> vert;
            int other = 7 ^ all[i].c ^ all[j].c;
            vert[all[i].a]++;
            vert[all[i].b]++;
            vert[all[j].a]++;
            vert[all[j].b]++;
            if (vert.size() != 3) continue;
            for (auto i : vert) {
                if (i.second == 2) vert.erase(i.first);
            }

            Edge seeking = {(*vert.begin()).first, (*next(vert.begin())).first, other};
            if (has.find(seeking) != has.end()) {
                cnt++;
            }
        }
        return (cnt == 3 * (n - 2));
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, n;
    cin >> t >> n;
    string s;
    cin >> s;
    FOR(i, 0, n - 3) {
        cin >> edges[i].a >> edges[i].b >> edges[i].c;
        if (edges[i].a > edges[i].b) swap(edges[i].a, edges[i].b);
        edges[i].c = (1 << (edges[i].c - 1));
    }
    FOR(i, 0, n) colour[i] = (1 << (s[i] - '1'));

    if (is_tri(n - 3)) {
        if (is_patriotic(n)) cout << "tocno";
        else cout << "neispravno bojenje";
    } else {
        cout << "neispravna triangulacija";
    }
    return 0;
}