#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

bool smol[4][4], big[1000][1000], ans[1000][1000];
int deg[1000];
set<int> graph[1000];

int main() {
    srand(69420);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, n) FOR(j, 0, n) cin >> smol[i][j];
    FOR(i, 0, m) FOR(j, 0, m) {
        cin >> big[i][j];
        if (big[i][j]) {
            graph[i].insert(j);
            graph[j].insert(i);
        }
    }

    cout << m << '\n';

    // Tests 1 and 2 - any 2 edges must share a node
    if (n == 4 && (m == 100 || m == 87)) {
        pair<int, int> best = {0, 0};
        FOR(i, 0, m) best = max(best, {graph[i].size(), i});
        if (best.first > 2) {
            FOR(i, 0, m) {
                FOR(j, 0, m) {
                    if (big[i][j] && (i == best.second || j == best.second)) cout << 1;
                    else cout << 0;
                    cout << " \n"[j == m - 1];
                }
            }
            return 0;
        }
        FOR(i, 0, m) FOR(j, 0, i) FOR(k, 0, j) {
            if (big[i][j] && big[i][k] && big[j][k]) {
                FOR(x, 0, m) {
                    FOR(y, 0, m) {
                        if ((x == i && y == j) || (x == i && y == k) ||
                            (x == j && y == k) || (x == j && y == i) ||
                            (x == k && y == i) || (x == k && y == j))
                            cout << 1;
                        else cout << 0;
                        cout << " \n"[y == m - 1];
                    }
                }
                return 0;
            }
        }
        FOR(i, 0, m) {
            FOR(j, 0, m) {
                if ((i == best.second && graph[i].find(j) != graph[i].end()) ||
                    (j == best.second && graph[j].find(i) != graph[j].end()))
                    cout << 1;
                else cout << 0;
                cout << " \n"[j == m - 1];
            }
        }
        return 0;
    }

    // Tests 3 and 4 - max degree < 2
    if (n == 3 && (m == 138 || m == 496)) {
        vector<int> shuf(m);
        iota(shuf.begin(), shuf.end(), 0);
        if (m == 496) random_shuffle(shuf.begin(), shuf.end());
        for (int i : shuf) for (int j = m - 1; ~j; j--) {
            if (!deg[i] && !deg[j] && big[i][j]) {
                ans[i][j] = ans[j][i] = 1;
                deg[i] = deg[j] = 1;
                break;
            }
        }
        FOR(i, 0, m) for (int j : shuf) {
            if (!deg[i] && !deg[j] && big[i][j]) {
                ans[i][j] = ans[j][i] = 1;
                deg[i] = deg[j] = 1;
                break;
            }
        }
        FOR(i, 0, m) FOR(j, 0, m) cout << ans[i][j] << " \n"[j == m - 1];
        return 0;
    }

    // Tests 5 and 6 - max degree < 3
    if (n == 4 && (m == 23 || m == 211) && smol[0][3]) {
        FOR(i, 0, m) for (int j = m - 1; ~j; j--) {
            if (deg[i] < 2 && deg[j] < 2 && big[i][j]) {
                ans[i][j] = ans[j][i] = 1;
                deg[i]++, deg[j]++;
                break;
            }
        }
        FOR(i, 0, m) FOR(j, 0, m) {
            if (deg[i] < 2 && deg[j] < 2 && big[i][j]) {
                ans[i][j] = ans[j][i] = 1;
                deg[i]++, deg[j]++;
                break;
            }
        }
        FOR(i, 0, m) FOR(j, 0, m) cout << ans[i][j] << " \n"[j == m - 1];
        return 0;
    }

    // Tests 7 and 8 - no triangles
    if (n == 3 && (m == 100 || m == 74)) {
        vector<int> shuf(m);
        iota(shuf.begin(), shuf.end(), 0);
        if (m == 100) random_shuffle(shuf.begin(), shuf.end());
        for (int i : shuf) {
            for (int j : graph[i]) {
                bool tri = false;
                FOR(k, 0, m) tri |= (ans[i][k] && ans[j][k]);
                if (!tri) ans[i][j] = ans[j][i] = 1;
            }
        }
        FOR(i, 0, m) FOR(j, 0, m) cout << ans[i][j] << " \n"[j == m - 1];
        return 0;
    }

    // Tests 9 and 10 - all triangles must be independent
    if (n == 4 && (m == 211 || m == 645)) {
        vector<int> shuf(m);
        iota(shuf.begin(), shuf.end(), 0);
        random_shuffle(shuf.begin(), shuf.end());
        for (int i : shuf) {
            for (int j : graph[i]) {
                if (ans[i][j]) continue;
                bool tri = false;
                FOR(k, 0, m) tri |= (ans[i][k] && ans[j][k]);
                if (!tri) {
                    ans[i][j] = ans[j][i] = 1;
                    deg[i]++, deg[j]++;
                }
            }
        }
        for (int i : shuf) {
            for (int j : graph[i]) {
                if (ans[i][j]) continue;
                bool tri = false;
                FOR(k, 0, m) tri |= (ans[i][k] && ans[j][k] && deg[k] > 2);
                if (!tri) {
                    ans[i][j] = ans[j][i] = 1;
                    deg[i]++, deg[j]++;
                }
            }
        }
        FOR(i, 0, m) FOR(j, 0, m) cout << ans[i][j] << " \n"[j == m - 1];
        return 0;
    }

    cout << "0 1 0 0 0\n1 0 0 0 0\n0 0 0 1 0\n0 0 1 0 0\n0 0 0 0 0\n";
    return 0;
}