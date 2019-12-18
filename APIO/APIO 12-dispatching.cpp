#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Node {
    priority_queue<int> *pq;
    ll s;
};

int n, m;
ll ans = 0;
vector<int> graph[100001];
pair<int, int> ninja[100001];
Node dp[100001];

void dfs(int node) {
    int mx = 0, mx_child = 0;
    for (int i : graph[node]) {
        dfs(i);
        if (dp[i].pq->size() > mx) {
            mx = dp[i].pq->size();
            mx_child = i;
        }
    }

    if (mx) {
        dp[node].pq = dp[mx_child].pq;
        dp[node].s = dp[mx_child].s;
    } else dp[node].pq = new priority_queue<int>();

    dp[node].pq->push(ninja[node].first);
    dp[node].s += ninja[node].first;
    for (int i : graph[node]) {
        if (i != mx_child) {
            while (dp[i].pq->size()) {
                int j = dp[i].pq->top();
                dp[i].pq->pop();

                dp[node].pq->push(j);
                dp[node].s += j;
            }
        }
    }
    while (dp[node].s > m) {
        dp[node].s -= dp[node].pq->top();
        dp[node].pq->pop();
    }

    ans = max(ans, ninja[node].second * (ll)dp[node].pq->size());
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, n + 1) {
        int b, c, l;
        cin >> b >> c >> l;
        graph[b].push_back(i);
        ninja[i] = {c, l};
    }

    dfs(1);
    cout << ans;
    return 0;
}