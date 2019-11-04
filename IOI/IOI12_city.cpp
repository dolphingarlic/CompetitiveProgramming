#include "grader.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
typedef long long ll;
using namespace std;

const ll MOD = 1e9;

int N;
pair<int, int> srtd[2][100001];
set<int> graphs[2][100001];
ll num_blocks[2][100001], dp[2][100001], ans = 0;
int x = 0, y = 0;
map<pair<int, int>, int> x_cmp, y_cmp;

void dfs1(int dir, int node, int parent = 0) {
    for (int i : graphs[dir][node]) if (i != parent) {
        dfs1(dir, i, node);
        dp[dir][node] += dp[dir][i];
        ans = (ans + (N - dp[dir][i]) * dp[dir][i]) % MOD;
    }
}

int DistanceSum(int N, int *X, int *Y) {
    ::N = N;
    FOR(i, 0, N) {
        srtd[0][i] = {X[i], Y[i]};
        srtd[1][i] = {Y[i], X[i]};
    }
    sort(srtd[0], srtd[0] + N);
    sort(srtd[1], srtd[1] + N);

    FOR(i, 0, N) {
        if (i == 0 || srtd[0][i].y - srtd[0][i - 1].y != 1 || srtd[0][i].x != srtd[0][i - 1].x)
            y++;
        dp[0][y]++;
        y_cmp[srtd[0][i]] = y;

        if (y_cmp[{srtd[0][i].x - 1, srtd[0][i].y}]) {
            graphs[0][y_cmp[{srtd[0][i].x - 1, srtd[0][i].y}]].insert(y);
            graphs[0][y].insert(y_cmp[{srtd[0][i].x - 1, srtd[0][i].y}]);
        }
    }
    FOR(i, 0, N) {
        if (i == 0 || srtd[1][i].y - srtd[1][i - 1].y != 1 || srtd[1][i].x != srtd[1][i - 1].x)
            x++;
        dp[1][x]++;
        x_cmp[srtd[1][i]] = x;

        if (x_cmp[{srtd[1][i].x - 1, srtd[1][i].y}]) {
            graphs[1][x_cmp[{srtd[1][i].x - 1, srtd[1][i].y}]].insert(x);
            graphs[1][x].insert(x_cmp[{srtd[1][i].x - 1, srtd[1][i].y}]);
        }
    }

    dfs1(0, 1);
    dfs1(1, 1);

    return (int)ans;
}
