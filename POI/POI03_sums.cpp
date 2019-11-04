#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int dp[50000], a[5000];

int main() {
    int n;
    scanf("%d", &n);
    FOR(i, 0, n) scanf("%d", &a[i]);
    fill(dp, dp + a[0], INT_MAX);

    priority_queue<pair<int, int>> pq;
    pq.push({0, 0});
    dp[0] = 0;
    while (pq.size()) {
        int curr = pq.top().second, mvs = pq.top().first;
        pq.pop();
        FOR(i, 1, n) {
            int d2 = mvs - a[i], v = (curr + a[i]) % a[0];
            if (dp[v] > -d2) {
                dp[v] = -d2;
                pq.push({d2, v});
            }
        }
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int x;
        scanf("%d", &x);
        if (dp[x % a[0]] > x) printf("NIE\n");
        else printf("TAK\n");
    }
    return 0;
}