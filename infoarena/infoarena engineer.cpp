#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Cell {
    int x, y, val;
    inline bool operator<(Cell B) { return val < B.val; }
} cells[1210000];

struct Query {
    int x1, y1, x2, y2, k, l, r;
} queries[1000];

int n, m, bit[1101][1101];
vector<int> to_check[1210000];

inline void update(int x, int y) {
    for (int i = x; i <= n; i += (i & (-i)))
        for (int j = y; j <= m; j += (j & (-j)))
            bit[i][j]++;
}

inline int query(int x, int y) {
    int ans = 0;
    for (int i = x; i; i -= (i & (-i)))
        for (int j = y; j; j -= (j & (-j)))
            ans += bit[i][j];
    return ans;
}

inline int query(Query Q) {
    return query(Q.x2, Q.y2) + query(Q.x1 - 1, Q.y1 - 1) - query(Q.x2, Q.y1 - 1) - query(Q.x1 - 1, Q.y2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("engineer.in");
    ofstream cout("engineer.out");

    cin >> n >> m;
    FOR(i, 0, n) FOR(j, 0, m) {
        cin >> cells[i * m + j].val;
        cells[i * m + j].x = i + 1, cells[i * m + j].y = j + 1;
    }
    sort(cells, cells + n * m);

    int q;
    cin >> q;
    FOR(i, 0, q) {
        cin >> queries[i].x1 >> queries[i].y1 >> queries[i].x2 >> queries[i].y2 >> queries[i].k;
        queries[i].l = 0, queries[i].r = n * m;
    }

    bool running = true;
    while (running) {
        running = false;

        FOR(i, 1, n + 1) FOR(j, 1, m + 1) bit[i][j] = 0;
        FOR(i, 0, q) if (queries[i].l != queries[i].r)
            to_check[(queries[i].l + queries[i].r) / 2].push_back(i);

        FOR(i, 0, n * m) {
            update(cells[i].x, cells[i].y);

            while (to_check[i].size()) {
                running = true;
                int j = to_check[i].back();
                to_check[i].pop_back();
                if (query(queries[j]) < queries[j].k) queries[j].l = i + 1;
                else queries[j].r = i;
            }
        }
    }

    FOR(i, 0, q) cout << cells[queries[i].l].val << '\n';
    return 0;
}