#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int v[200], a[200], demand[200];

int main() {
    int n, m = 0;
    cin >> n;
    FOR(i, 0, n) {
        cin >> v[i];
        m += v[i];
        a[i] = v[i];
    }
    m /= n;

    demand[0] = 0;
    FOR(i, 1, n - 1) {
        demand[i] = m - a[i - 1];
        a[i - 1] += demand[i], a[i] -= 2 * demand[i], a[i + 1] += demand[i];
    }
    demand[n - 1] = m - a[n - 2];

    int d = *min_element(demand, demand + n);
    FOR(i, 0, n) demand[i] -= d;
    FOR(i, 1, n - 1) demand[i] *= 2;

    vector<pair<int, int>> moves;
    while (*max_element(v, v + n) > m) {
        bool can_fulfill = false;
        FOR(i, 0, n) {
            if (demand[i] && v[i] >= demand[i]) {
                can_fulfill = true;

                if (i == 0) {
                    moves.push_back({i + 1, demand[i]});
                    v[i + 1] += demand[i];
                    v[i] -= demand[i];
                    demand[i] = 0;
                } else if (i == n - 1) {
                    moves.push_back({i + 1, demand[i]});
                    v[i - 1] += demand[i];
                    v[i] -= demand[i];
                    demand[i] = 0;
                } else {
                    moves.push_back({i + 1, demand[i] / 2});
                    v[i + 1] += demand[i] / 2;
                    v[i - 1] += demand[i] / 2;
                    v[i] -= demand[i];
                    demand[i] = 0;
                }
            }
        }

        if (!can_fulfill) {
            int i = max_element(v, v + n) - v;
            int trans = v[i] / 2 * 2;
            demand[i] -= trans;

            if (i == 0) {
                moves.push_back({i + 1, trans});
                v[i + 1] += trans;
                v[i] -= trans;
            } else if (i == n - 1) {
                moves.push_back({i + 1, trans});
                v[i - 1] += trans;
                v[i] -= trans;
            } else {
                moves.push_back({i + 1, trans / 2});
                v[i + 1] += trans / 2;
                v[i - 1] += trans / 2;
                v[i] -= trans;
            }
        }
    }

    cout << moves.size() << '\n';
    for (auto& i : moves) {
        cout << i.first << ' ' << i.second << '\n';
    }
    return 0;
}
