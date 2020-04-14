/*
Balkan 2011 TimeisMoney
- Magic geometry stuff
- http://www.boi2011.ro/resurse/tasks/timeismoney-sol.pdf
- Complexity: O(Good enough)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m;

struct Line {
    int u, v;
    ll t, c, w;

    bool operator<(Line B) { return w < B.w; }
} lines[10000];

struct Point { ll x, y; };

bool collinear(Point A, Point B, Point C) {
    return (B.x - A.x) * (C.y - A.y) == (B.y - A.y) * (C.x - A.x);
}

int cmp[200];

int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

void onion(int A, int B) { cmp[find(A)] = cmp[find(B)]; }

ll best_t = INT_MAX, best_c = INT_MAX;
vector<Line> best_res;

Point mst(ll dx, ll dy) {
    FOR(i, 0, m) lines[i].w = dy * lines[i].t + dx * lines[i].c;
    sort(lines, lines + m);
    iota(cmp, cmp + n, 0);

    ll t = 0, c = 0;
    vector<Line> res;
    FOR(i, 0, m) {
        if (find(lines[i].u) != find(lines[i].v)) {
            t += lines[i].t;
            c += lines[i].c;
            onion(lines[i].u, lines[i].v);
            res.push_back(lines[i]);
        }
    }
    if (t * c < best_t * best_c) {
        best_t = t, best_c = c;
        best_res = res;
    }

    return {t, c};
}

void recurse(Point A, Point B) {
    Point C = mst(B.x - A.x, A.y - B.y);
    if (collinear(A, B, C)) return;
    recurse(A, C);
    recurse(C, B);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 0, m) cin >> lines[i].u >> lines[i].v >> lines[i].t >> lines[i].c;

    Point A = mst(0, 1), B = mst(1, 0);
    recurse(A, B);

    cout << best_t << ' ' << best_c << '\n';
    for (Line i : best_res) cout << i.u << ' ' << i.v << '\n';
    return 0;
}