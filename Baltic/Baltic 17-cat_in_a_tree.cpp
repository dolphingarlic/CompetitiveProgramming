#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, d;
vector<int> graph[200001];
// dp: Maximum number of marked nodes in subtree of i
// to_root: Minimum length of path from a marked node to the root
// mn_dist: Maximum length of path from a marked node to the root after
// the erasing of another marked node
int dp[200001], to_root[200001], mn_dist[200001];

void dfs(int node = 0) {
    if (graph[node].size()) {
        int v = graph[node][0];
        dfs(v);

        if (to_root[v] + 1 >= d) {
            // We mark the root
            dp[node] = dp[v] + 1;
            to_root[node] = 0;
            mn_dist[node] = to_root[v] + 1;
        } else {
            // We don't
            dp[node] = dp[v];
            to_root[node] = to_root[v] + 1;
            mn_dist[node] = mn_dist[v] + 1;
        }

        FOR(i, 1, graph[node].size()) {
            int v = graph[node][i];
            dfs(v);

            int doo = to_root[node] + to_root[v] + 1;
            int mdoo = min(to_root[node], to_root[v] + 1);
            
            int dos = to_root[node] + mn_dist[v] + 1;
            int mdos = min(to_root[node], mn_dist[v] + 1);
    
            int dso = mn_dist[node] + to_root[v] + 1;
            int mdso = min(mn_dist[node], to_root[v] + 1);
    
            int dss = mn_dist[node] + mn_dist[v] + 1;
            int mdss = min(mn_dist[node], mn_dist[v] + 1);

            if (doo >= d) {
                dp[node] += dp[v];
                to_root[node] = mdoo;
                mn_dist[node] = max(mdos, mdso);
            } else {
                dp[node] += dp[v] - 1;

                if (dos >= d) to_root[node] = mdos;
                else to_root[node] = 0;

                if (dso >= d) to_root[node] = max(to_root[node], mdso);

                mn_dist[node] = mdss;
            }
        }
    } else {
        dp[node] = 1;
        to_root[node] = 0;
        mn_dist[node] = d;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> d;
    FOR(i, 1, n) {
        int p;
        cin >> p;
        graph[p].push_back(i);
    }

    dfs();
    cout << dp[0];
    return 0;
}