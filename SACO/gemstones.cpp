#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;

int c[200001], dp[200001][2];
map<pair<int, int>, int> has_diag;
vector<int> graph[200001], has_colour[200001];

void dfs(int node, int parent = 0) {
    dp[node][1] = 1;
    for (int i : graph[node]) {
        if (!dp[i][0] && !dp[i][1]) {
            dfs(i, node);
            dp[node][0] += max(dp[i][0], dp[i][1]);
            dp[node][1] += dp[i][0];
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 2; i < n; i++) {
        int x, y, z;
        cin >> x >> y >> z >> c[i];
        has_colour[c[i]].push_back(i);
        // Each diagonal has two incident triangles
        for (pair<int, int> p : vector<pair<int, int>>{{x, y}, {y, z}, {z, x}}) {
            if (has_diag.count(p) && c[i] == c[has_diag[p]]) {
                graph[i].push_back(has_diag[p]);
                graph[has_diag[p]].push_back(i);
            } else {
                has_diag[p] = has_diag[{p.second, p.first}] = i;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n - 2; i++) {
        int cand = 0;
        for (int j : has_colour[i]) {
            if (!dp[j][0] && !dp[j][1]) {
                dfs(j);
                cand += max(dp[j][0], dp[j][1]);
            }
        }
        ans = max(ans, cand);
    }
    cout << ans << '\n';
}
