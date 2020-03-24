#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int k[1000001];
pair<int, int> dp[1000001];
vector<int> graph[1000001];

void dfs(int node = 1) {
    dp[node] = {1, 1};
    for (int i : graph[node]) {
        dfs(i);
        if (dp[i].first + 1 > dp[node].first) dp[node] = {dp[i].first + 1, 1};
        if (dp[i].first + 1 == dp[node].first) dp[node].second++;
    }
}

struct Cmp {
    bool operator()(const int& A, const int& B) { return dp[A] < dp[B]; }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    FOR(i, 0, q) cin >> k[i];
    sort(k, k + q);
    FOR(i, 1, n) {
        int p;
        cin >> p;
        graph[p].push_back(i + 1);
    }
    dfs();

    int ans = 0, ptr = 0;
    priority_queue<int, vector<int>, Cmp> pq;
    pq.push(1);
    while (pq.size()) {
        if (ptr == 0) ans++;
        vector<int> to_process;
        for (int i = 0; pq.size() && i < k[ptr]; i++) {
            to_process.push_back(pq.top());
            pq.pop();
        }
        for (int i : to_process) for (int j : graph[i]) pq.push(j);
        ptr++;
        if (ptr == q) ptr = 0;
    }
    cout << ans;
    return 0;
}