#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;
 
pair<int, int> roads[100000];
vector<pair<int, int>> graph[100001];
bool is_shop[100001];
int tin[100001], tout[100001], level[100001], indx = 0;
 
pair<int, ll> bl[100001][20];
ll dp1[100001], dp2[100001][20];
 
void dfs(int node, int parent = 0, int depth = 0) {
    tin[node] = indx++;
    level[node] = depth;
    dp1[node] = (is_shop[node] ? 0 : 1ll << 60);
    FOR(i, 1, 20) {
        bl[node][i] = {
            bl[bl[node][i - 1].first][i - 1].first,
            bl[node][i - 1].second + bl[bl[node][i - 1].first][i - 1].second};
    }
 
    for (auto& i : graph[node]) {
        if (i.first != parent) {
            bl[i.first][0] = {node, i.second};
            dfs(i.first, node, depth + 1);
            dp1[node] = min(dp1[node], dp1[i.first] + i.second);
        }
    }
 
    tout[node] = indx++;
}
void dfs2(int node, int parent = 0, int dist = 0) {
    dp2[node][0] = dp1[parent] + dist;
    FOR(i, 1, 20) {
        dp2[node][i] = min(dp2[node][i - 1], dp2[bl[node][i - 1].first][i - 1] +
                                                 bl[node][i - 1].second);
    }
    for (auto& i : graph[node]) {
        if (i.first != parent) dfs2(i.first, node, i.second);
    }
}
 
bool is_ancestor(int u, int v) {
    return (tin[u] >= tin[v] && tout[u] <= tout[v]);
}
 
int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, s, q, e;
    cin >> n >> s >> q >> e;
    FOR(i, 1, n) {
        int a, b, w;
        cin >> a >> b >> w;
        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
        roads[i] = {a, b};
    }
    FOR(i, 0, s) {
        int x;
        cin >> x;
        is_shop[x] = true;
    }
    dfs(e);
    dfs2(e);
 
    while (q--) {
        int i, r;
        cin >> i >> r;
        if (is_ancestor(r, roads[i].first) && is_ancestor(r, roads[i].second)) {
            if (tin[roads[i].first] < tin[roads[i].second])
                swap(roads[i].first, roads[i].second);
            int dist = level[r] - level[roads[i].first];
            ll ans = dp1[r];
 
            ll len = 0;
            int pw = 0;
            while (dist) {
                if (dist & 1) {
                    ans = min(ans, len + dp2[r][pw]);
                    len += bl[r][pw].second;
                    r = bl[r][pw].first;
                }
                dist >>= 1;
                pw++;
            }
 
            if (ans == 1ll << 60)
                cout << "oo\n";
            else
                cout << ans << '\n';
        } else
            cout << "escaped\n";
    }
    return 0;
}