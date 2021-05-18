#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int INF = 1e9;

vector<int> graph[100001];
int c[100001], black, white, opt[100001], dp[2][100001];
pair<int, int> dfs_res[100001];

pair<int, int> dfs1(int node = 1, int parent = 1) {
    pair<int, int> ans = {INF, INF};
    if (c[node]) {
        dp[0][node] = 0;
        dp[1][node] = INF;
        ans.second = 0;
    } else {
        dp[1][node] = 0;
        dp[0][node] = INF;
        ans.first = 0;
    }

    for (int i : graph[node])
        if (i != parent) {
            pair<int, int> ret = dfs1(i, node);
            ans.first = min(ans.first, ret.first + 1);
            ans.second = min(ans.second, ret.second + 1);
            dp[0][node] = min(dp[0][node], ret.first + 1);
            dp[1][node] = min(dp[1][node], ret.second + 1);
        }
    return dfs_res[node] = ans;
}

void dfs2(int node = 1, int parent = 0, int to_black = INF,
          int to_white = INF) {
    dp[0][node] = min(dp[0][node], to_black + 1);
    dp[1][node] = min(dp[1][node], to_white + 1);

    vector<int> to_black_pref = {INF}, to_black_suff = {INF}, to_white_pref = {INF}, to_white_suff = {INF};
    for (int i : graph[node]) if (i != parent) {
        to_black_pref.push_back(dfs_res[i].first);
        to_black_suff.push_back(dfs_res[i].first);
        to_white_pref.push_back(dfs_res[i].second);
        to_white_suff.push_back(dfs_res[i].second);
    }
    for (int i = 1; i < to_black_pref.size(); i++) {
        to_black_pref[i] = min(to_black_pref[i], to_black_pref[i - 1]);
        to_white_pref[i] = min(to_white_pref[i], to_white_pref[i - 1]);
    }
    for (int i = to_black_suff.size() - 2; ~i; i--) {
        to_black_suff[i] = min(to_black_suff[i], to_black_suff[i + 1]);
        to_white_suff[i] = min(to_white_suff[i], to_white_suff[i + 1]);
    }
    to_black_suff.push_back(INF);
    to_white_suff.push_back(INF);

    int idx = 1;
    for (int i : graph[node]) if (i != parent) {
        int new_to_black = min({to_black + 1, to_black_pref[idx - 1] + 1, to_black_suff[idx + 1] + 1});
        int new_to_white = min({to_white + 1, to_white_pref[idx - 1] + 1, to_white_suff[idx + 1] + 1});
        if (c[node] == 0) new_to_black = 0;
        if (c[node] == 1) new_to_white = 0;

        dfs2(i, node, new_to_black, new_to_white);
        idx++;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) graph[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        black = 0, white = 0;
        for (int i = 1; i <= n; i++) {
            cin >> c[i];
            if (n <= 17) {
                black <<= 1, white <<= 1;
                if (c[i] == 0) black++;
                if (c[i] == 1) white++;
            } else {
                opt[i] = c[i];
            }
        }

        if (n <= 17) {
            int ans = INF;
            for (int mask = 0; mask < (1 << n); mask++) {
                if ((black & ~mask) == black && (white & mask) == white) {
                    for (int i = 1; i <= n; i++)
                        c[n - i + 1] = (mask & (1 << i - 1)) >> (i - 1);
                    dfs1();
                    dfs2();
                    int pot = max(*max_element(dp[0] + 1, dp[0] + n + 1),
                                  *max_element(dp[1] + 1, dp[1] + n + 1));
                    if (pot < ans) {
                        ans = pot;
                        for (int i = 1; i <= n; i++) opt[i] = c[i];
                    }
                }
            }
            if (ans == INF) {
                cout << "-1\n";
            } else {
                cout << ans << '\n';
                for (int i = 1; i <= n; i++) cout << opt[i] << ' ';
                cout << '\n';
            }
        } else {
            dfs1();
            dfs2();
            int ans = max(*max_element(dp[0] + 1, dp[0] + n + 1),
                          *max_element(dp[1] + 1, dp[1] + n + 1));
            if (ans == INF) {
                cout << "-1\n";
            } else {
                cout << ans << '\n';
                for (int i = 1; i <= n; i++) cout << opt[i] << ' ';
                cout << '\n';
            }
        }
    }
    return 0;
}
