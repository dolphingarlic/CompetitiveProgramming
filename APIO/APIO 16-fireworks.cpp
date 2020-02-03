#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Node {
    ll a, b, c;
    priority_queue<ll> *pq;
};

Node dp[300001];
vector<int> graph[300001];

void dfs(int node = 1) {
    if (graph[node].size()) {
        int mx_cnt = 0, mx_child = 0;
        for (int i : graph[node]) {
            dfs(i);
            dp[node].a += dp[i].a;
            dp[node].b += dp[i].b;
            if (dp[i].pq->size() > mx_cnt)
                mx_cnt = dp[i].pq->size(), mx_child = i;
        }

        dp[node].pq = dp[mx_child].pq;
        for (int i : graph[node])
            if (i != mx_child)
                while (dp[i].pq->size()) {
                    dp[node].pq->push(dp[i].pq->top());
                    dp[i].pq->pop();
                }

        while (dp[node].a > 1) {
            dp[node].a--;
            dp[node].b += dp[node].pq->top();
            dp[node].pq->pop();
        }

        ll slope1 = dp[node].pq->top();
        dp[node].pq->pop();
        ll slope0 = dp[node].pq->top();
        dp[node].pq->pop();
        
        dp[node].pq->push(slope1 + dp[node].c);
        dp[node].pq->push(slope0 + dp[node].c);

        dp[node].b -= dp[node].c;
    } else {
        dp[node].a = 1, dp[node].b = -dp[node].c;
        dp[node].pq->push(dp[node].c);
        dp[node].pq->push(dp[node].c);
    }
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    FOR(i, 1, n + m + 1) dp[i].pq = new priority_queue<ll>;
    FOR(i, 2, n + m + 1) {
        int p, c;
        cin >> p >> c;
        graph[p].push_back(i);
        dp[i].c = c;
    }

    dfs();
    if (dp[1].a) dp[1].b += dp[1].pq->top();

    cout << dp[1].b;
    return 0;
}