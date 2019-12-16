#include "werewolf.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

vector<int> dsu_tree[2][200000], graph[200000];
int N, p[2][20][200000], cnt, cmp[2][200000], order[2][200000];
pair<int, int> bounds[2][200000];

void dfs(int node, int t) {
    bounds[t][node] = {cnt, cnt};
    order[t][cnt] = node;
    cnt++;

    FOR(i, 1, 20) {
        if (p[t][i - 1][node] == -1) break;
        p[t][i][node] = p[t][i - 1][p[t][i - 1][node]];
    }

    for (int i : dsu_tree[t][node]) {
        p[t][0][i] = node;
        dfs(i, t);
        bounds[t][node].second = max(bounds[t][node].second, bounds[t][i].second);
    }
}

int find(int a, int t) {
    while (a != cmp[t][a]) cmp[t][a] = cmp[t][cmp[t][a]], a = cmp[t][a];
    return a;
}
void onion(int a, int b, int t) {
    cmp[t][find(a, t)] = cmp[t][find(b, t)];
}

vector<int> seg[800000];
void build(int node = 1, int l = 0, int r = N - 1) {
    if (l == r) seg[node] = {bounds[0][order[1][l]].first};
    else {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        
        int lptr = 0, rptr = 0;
        int lsz = seg[node * 2].size(), rsz = seg[node * 2 + 1].size();
        while (lptr < lsz && rptr < rsz) {
            if (seg[node * 2][lptr] < seg[node * 2 + 1][rptr]) {
                seg[node].push_back(seg[node * 2][lptr++]);
            } else {
                seg[node].push_back(seg[node * 2 + 1][rptr++]);
            }
        }
        while (lptr < lsz) seg[node].push_back(seg[node * 2][lptr++]);
        while (rptr < rsz) seg[node].push_back(seg[node * 2 + 1][rptr++]);
    }
}

bool query(int a, int b, int x, int y, int node = 1, int l = 0, int r = N - 1) {
    if (r < a || l > b) return 0;
    if (r <= b && l >= a) return (upper_bound(seg[node].begin(), seg[node].end(), y) - lower_bound(seg[node].begin(), seg[node].end(), x) != 0);

    int mid = (l + r) / 2;
    return (query(a, b, x, y, node * 2, l, mid) || query(a, b, x, y, node * 2 + 1, mid + 1, r));
}

vector<int> check_validity(int N, vector<int> X, vector<int> Y, vector<int> S, vector<int> E, vector<int> L, vector<int> R) {
    ::N = N;
    int Q = S.size();
    vector<int> A(Q);

    FOR(i, 0, N) cmp[0][i] = cmp[1][i] = i;
    FOR(i, 0, X.size()) {
        graph[X[i]].push_back(Y[i]);
        graph[Y[i]].push_back(X[i]);
    }

    for (int i = N - 1; ~i; i--)
        for (int j : graph[i])
            if (j > i && find(j, 0) != find(i, 0)) {
                dsu_tree[0][i].push_back(find(j, 0));
                onion(j, i, 0);
            }
    for (int i = 0; i < N; i++)
        for (int j : graph[i])
            if (j < i && find(j, 1) != find(i, 1)) {
                dsu_tree[1][i].push_back(find(j, 1));
                onion(j, i, 1);
            }

    memset(p, -1, sizeof(p));

    cnt = 0;
    dfs(0, 0);
    cnt = 0;
    dfs(N - 1, 1);

    build();

    FOR(i, 0, Q) {
        int X = S[i], Y = E[i];
        for (int j = 19; ~j; j--) {
            if (~p[0][j][X] && p[0][j][X] >= L[i]) X = p[0][j][X];
            if (~p[1][j][Y] && p[1][j][Y] <= R[i]) Y = p[1][j][Y];
        }
        A[i] = query(bounds[1][Y].first, bounds[1][Y].second, bounds[0][X].first, bounds[0][X].second);
    }

    return A;
}
