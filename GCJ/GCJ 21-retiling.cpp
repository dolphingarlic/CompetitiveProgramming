#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<vector<int>> g;
vector<int> mt;
vector<bool> used;

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

char orig[11][11], targ[11][11];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    for (int test = 1; test <= t; test++) {
        int n, m, f, s;
        cin >> n >> m >> f >> s;
        g.resize(n * m);
        g.assign(n * m, vector<int>());
        mt.resize(n * m);
        used.resize(n * m);
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            cin >> orig[i][j];
        int bad_cnt = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
            cin >> targ[i][j];
            if (targ[i][j] != orig[i][j]) {
                bad_cnt++;
                if (i > 0 && targ[i - 1][j] != orig[i - 1][j] && targ[i][j] != targ[i - 1][j]) {
                    if (i + j & 1) g[(i - 1) * m + j].push_back(i * m + j);
                    else g[i * m + j].push_back((i - 1) * m + j);
                }
                if (j > 0 && targ[i][j - 1] != orig[i][j - 1] && targ[i][j] != targ[i][j - 1]) {
                    if (i + j & 1) g[i * m + j - 1].push_back(i * m + j);
                    else g[i * m + j].push_back(i * m + j - 1);
                }
            }
        }
        mt.assign(n * m, -1);
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (i + j + 1 & 1) {
            used.assign(n * m, false);
            try_kuhn(i * m + j);
        }
        int mat = 0;
        for (int i = 0; i < n * m; i++) if (mt[i] != -1) {
            mat++;
            // cerr << i << ' ' << mt[i] << '\n';
        }
        cout << "Case #" << test << ": " << bad_cnt - mat << '\n';
        g.clear();
        mt.clear();
        used.clear();
    }
    return 0;
}
