#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct pair_hash {
    inline size_t operator()(const pair<int,int> & v) const {
        return (v.first<<11)+v.second;
    }
};

int l, w, k;
char grid[1026][1026];
int cmp = 1, v[1026][1026];
vector<pair<int, int>> d = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

inline bool available(int x, int y) {
    return grid[x][y] == '.' && !v[x][y] &&
           v[x + 1][y] + v[x - 1][y] + v[x][y + 1] + v[x][y - 1] ==
               max({v[x + 1][y], v[x - 1][y], v[x][y + 1], v[x][y - 1]});
}

int bfs(int x, int y) {
    unordered_set<pair<int, int>, pair_hash> q, added = {{x, y}};
    v[x][y] = cmp;
    for (pair<int, int> i : d) if (available(x + i.first, y + i.second))
        q.insert({x + i.first, y + i.second});

    while (q.size()) {
        vector<pair<int, int>> to_erase;
        pair<int, pair<int, int>> best;
        for (pair<int, int> i : q) {
            if (!available(i.first, i.second)) to_erase.push_back(i);
            else {
                int cnt = 0;
                for (pair<int, int> j : d) cnt += available(i.first + j.first, i.second + j.second);
                best = max(best, {cnt, i});
            }
        }
        for (pair<int, int> i : to_erase) q.erase(i);
        q.erase(best.second);

        tie(x, y) = best.second;
        v[x][y] = cmp;
        added.insert({x, y});
        // if (added.size() % 10000 == 0) cerr << added.size() << endl;

        for (pair<int, int> i : d) {
            if (available(x + i.first, y + i.second)) {
                v[x + i.first][y + i.second] = cmp;
                added.insert({x + i.first, y + i.second});
                // if (added.size() % 10000 == 0) cerr << added.size() << endl;
                for (pair<int, int> j : d) {
                    if (available(x + i.first + j.first, y + i.second + j.second))
                        q.insert({x + i.first + j.first, y + i.second + j.second});
                }
            }
        }
    }
    cerr << "Done adding!" << endl;

    int ret = 0;
    for (pair<int, int> i : added) {
        v[i.first][i.second] = 0;
        ret += available(i.first, i.second);
        v[i.first][i.second] = cmp;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    srand(652365);
    cin >> l >> w >> k;
    FOR(i, 1, l + 1) FOR(j, 1, w + 1) cin >> grid[i][j];

    vector<pair<int, int>> to_process;
    FOR(i, 1, l + 1) FOR(j, 1, w + 1) to_process.push_back({i, j});
    random_shuffle(to_process.begin(), to_process.end());

    pair<int, pair<int, int>> opt = {0, {1, 1}};
    cerr << "Starting..." << endl;
    for (pair<int, int> i : to_process) if (available(i.first, i.second)) {
        opt = max(opt, {bfs(i.first, i.second), {i.first, i.second}});
        cerr << "BFSed " << cmp << " times" << endl;
        cmp++;
        if (cmp == 11) break;
    }
    cerr << k << ' ' << opt.first << ' ' << min(10.0, 10.0 * opt.first / k) << endl;

    FOR(i, 1, l + 1) {
        FOR(j, 1, w + 1) {
            if (grid[i][j] == '.' &&
                v[i][j] != v[opt.second.first][opt.second.second])
                cout << 'X';
            else
                cout << grid[i][j];
        }
        cout << '\n';
    }
    return 0;
}