/*
COCI 2015 Domino
- https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2016/contest3_solutions/solutions.pdf
- I hate this problem
*/

#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Domino {
    int val;
    pair<int, int> A, B;

    bool operator<(Domino X) { return val > X.val; }

    bool overlap(Domino X) {
        return A == X.A || A == X.B || B == X.A || B == X.B;
    }
};

bool graph[51][51], visited[1 << 20];
int a[2000][2000], dp[1 << 20], ans = 0;
vector<int> subgraph_a, subgraph_b;
Domino dominoes[10000000];

int D, K, n;

void dp_a(int mask) {
    if (visited[mask]) return;
    visited[mask] = true;

    if (__builtin_popcount(mask) == D) {
        subgraph_a.clear();
        FOR(i, 0, 20) {
            if (mask & (1 << i)) subgraph_a.push_back(i);
        }
        FOR(i, 0, D) FOR(j, i + 1, D) {
            if (!graph[subgraph_a[i]][subgraph_a[j]]) return;
        }
        for (int i : subgraph_a) dp[mask] += dominoes[i].val;
    } else if (__builtin_popcount(mask) > D) {
        FOR(i, 0, 20) {
            if (mask & (1 << i)) {
                dp_a(mask - (1 << i));
                dp[mask] = max(dp[mask], dp[mask - (1 << i)]);
            }
        }
    }
}

void dp_b(int idx, int possible) {
    if (idx == 51) return;
    if (subgraph_b.size() == K - D) {
        int local = dp[possible];
        for (int i : subgraph_b) local += dominoes[i].val;
        ans = max(ans, local);
    } else {
        dp_b(idx + 1, possible);

        for (int i : subgraph_b) if (!graph[i][idx]) return;
        FOR(i, 0, 20) {
            if (possible & (1 << i) && !graph[i][idx]) possible -= (1 << i);
        }
        subgraph_b.push_back(idx);
        if (dp[possible]) dp_b(idx + 1, possible);
        subgraph_b.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll tot = 0;
    cin >> n >> K;
    FOR(i, 0, n) FOR(j, 0, n) {
        cin >> a[i][j];
        tot += a[i][j];
    }

    int cnt = 0;
    FOR(i, 0, n) FOR(j, 1, n) {
        dominoes[cnt++] = {a[i][j - 1] + a[i][j], {i, j - 1}, {i, j}};
        dominoes[cnt++] = {a[j - 1][i] + a[j][i], {j - 1, i}, {j, i}};
    }
    sort(dominoes, dominoes + cnt);
    FOR(i, cnt, 51) dominoes[i] = {0, {0, 0}, {0, 0}};

    FOR(i, 0, 51) FOR(j, i + 1, 51) {
        graph[i][j] = graph[j][i] = !dominoes[i].overlap(dominoes[j]);
    }
    
    for (D = 0; D <= K; D++) {
        FOR(i, 0, 1 << 20) dp[i] = visited[i] = 0;
        dp_a((1 << 20) - 1);
        dp_b(20, (1 << 20) - 1);
    }

    cout << tot - ans;
    return 0;
}