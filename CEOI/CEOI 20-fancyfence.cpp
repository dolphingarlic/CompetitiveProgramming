#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

int n, m = 0;
ll h[100002], w[100002];
ll node_h[100002], node_w[100002], ans = 0;
pair<ll, int> srt[100002];
int cmp[100002], nd[100002], cnt = 0;
set<int> graph[100002];

int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

void onion(int A, int B) {
    if (find(A) == find(B)) return;
    node_w[nd[find(B)]] += node_w[nd[find(A)]];
    if (node_w[nd[find(B)]] >= MOD) node_w[nd[find(B)]] -= MOD;
    graph[nd[find(B)]].insert(nd[find(A)]);
    nd[find(A)] = nd[find(B)];
    cmp[find(A)] = cmp[find(B)];
}

ll c2(ll num) { return num * (num - 1) % MOD * 500000004 % MOD; }

void dfs(int node, ll depth, ll prv = 0) {
    ans += c2(node_w[node] + 1) * (c2(depth - prv + 1) + (depth - prv) * prv % MOD) % MOD;
    if (ans >= MOD) ans -= MOD;
    for (int i : graph[node]) dfs(i, node_h[i], depth);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        srt[i] = {h[i], i};
    }
    for (int i = 1; i <= n; i++) cin >> w[i];
    sort(srt + 1, srt + n + 1, greater<pair<ll, int>>());

    iota(cmp + 1, cmp + n + 1, 1);
    for (int i = 1, j = 1; i <= n; i = j) {
        while (j <= n && srt[j].first == srt[i].first) j++;
        for (int k = i; k < j; k++) {
            int x = srt[k].second;
            if (k == i || find(x) != find(srt[k - 1].second)) {
                nd[x] = ++cnt;
                node_h[cnt] = h[x];
                node_w[cnt] = w[x];
            } else {
                node_w[cnt] += w[x];
                if (node_w[cnt] >= MOD) node_w[cnt] -= MOD;
            }
            if (h[x] < h[x + 1]) onion(x + 1, x);
            if (h[x] <= h[x - 1]) onion(x - 1, x);
        }
    }

    dfs(cnt, node_h[cnt]);
    cout << ans << '\n';
    return 0;
}