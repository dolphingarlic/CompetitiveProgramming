#include "traffic.h"

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll n, a[1000000], dp2[1000000], totsum = 0, ans = LLONG_MAX, city;
vector<ll> graph[1000000];
pair<ll, ll> dp1[1000000];

void dfs(ll node, ll parent = -1) {
    dp1[node] = {0, a[node]};
    for (ll i : graph[node]) {
        if (i == parent) continue;
        dfs(i, node);
        dp1[node].first = max(dp1[node].first, dp1[i].second);
        dp1[node].second += dp1[i].second;
    }
    dp2[node] = totsum - dp1[node].second;
    if (ans > max(dp1[node].first, dp2[node])) ans = max(dp1[node].first, dp2[node]), city = node;
}

int LocateCentre(int N, int A[], int S[], int D[]) {
    n = N;
    FOR(i, 0, n) {
        a[i] = A[i];
        totsum += a[i];
    }
    FOR(i, 0, n - 1) {
        graph[S[i]].push_back(D[i]);
        graph[D[i]].push_back(S[i]);
    }
    dfs(0);
    return city;
}