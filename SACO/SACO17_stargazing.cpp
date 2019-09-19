#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Point {
    int x, y, t;
};

const int MAXN = 2000001;

int seg[4][4 * MAXN];
Point stars[100001];
pair<Point, int> events[200001];
vector<int> graph[100001];

int component[100001], sz[100001];

bool cmp(pair<Point, int> a, pair<Point, int> b) {
    if (a.first.y == b.first.y) {
        if (a.second == b.second) return a.first.x < b.first.x;
        return a.second > b.second;
    }
    return a.first.y < b.first.y;
}

int find(int a) {
    while (a != component[a]) component[a] = component[component[a]], a = component[a];
    return a;
}
void onion(int a, int b) {
    if (sz[find(a)] > sz[find(b)]) swap(a, b);
    if (find(a) != find(b)) {
        sz[find(b)] += sz[find(a)];
        component[find(a)] = component[find(b)];
    }
}

void update(int s, int pos, int val, int node = 1, int l = 1, int r = MAXN) {
    if (l == r) seg[s][node] = val;
    else {
        int mid = (l + r) / 2;
        if (pos <= mid) update(s, pos, val, node * 2, l, mid);
        else update(s, pos, val, node * 2 + 1, mid + 1, r);
        seg[s][node] = min(seg[s][node * 2], seg[s][node * 2 + 1]);
    }
}
int query(int s, int a, int b, int node = 1, int l = 1, int r = MAXN) {
    if (l > b || r < a) return INT_MAX;
    if (l >= a && r <= b) return seg[s][node];
    int mid = (l + r) / 2;
    return min(query(s, a, b, node * 2, l, mid),
               query(s, a, b, node * 2 + 1, mid + 1, r));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, d;
    cin >> n >> d;
    FOR(i, 1, n + 1) {
        int x, y;
        cin >> x >> y;
        stars[i] = {x + y + 1, x - y + 1000001, i};
    }
    FOR(i, 1, n + 1) component[i] = i, sz[i] = 1;

    FOR(i, 0, 4) {
        FOR(j, 1, n + 1) {
            events[j] = {stars[j], 0}, events[j + n] = {stars[j], 1};
            events[j + n].first.y += d + 1;
        }
        sort(events + 1, events + 2 * n + 1, cmp);
        fill(seg[i], seg[i] + 4 * MAXN, INT_MAX);

        FOR(j, 1, 2 * n + 1) {
            if (events[j].second == 1) update(i, events[j].first.x, INT_MAX);
            else {
                int q = query(i, max(1, events[j].first.x - d), events[j].first.x);
                if (q < events[j].first.t) graph[events[j].first.t].push_back(q);
                update(i, events[j].first.x, events[j].first.t);
            }
        }

        FOR(j, 1, n + 1) stars[j] = {-stars[j].y + 2000002, stars[j].x, stars[j].t};
    }

    FOR(i, 1, n + 1) {
        for (int j : graph[i]) onion(i, j);
        cout << sz[find(i)] << '\n';
    }

    return 0;
}