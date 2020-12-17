/*
CEOI 2020 Star Trek
- https://codeforces.com/blog/entry/81919
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

vector<int> graph[100001];
ll win_as_root[100001], critical[100001];

ll expo(ll base, ll pow) {
    ll ans = 1;
    while (pow) {
        if (pow & 1) ans = ans * base % MOD;
        pow >>= 1, base = base * base % MOD;
    }
    return ans;
}

void dfs1(int node = 1, int parent = 0) {
    for (int i : graph[node]) if (i != parent) {
        dfs1(i, node);
        win_as_root[node] += (win_as_root[i] == 0);
    }
    if (!win_as_root[node]) critical[node] = 1;
    for (int i : graph[node]) if (i != parent) {
        if ((win_as_root[node] == 1 && !win_as_root[i]) || !win_as_root[node])
            critical[node] += critical[i];
    }
}

void dfs2(int node = 1, int parent = 0, bool par_win = true, ll par_crit = 0) {
    win_as_root[node] += !par_win;
    ll all_crit = 0, lose_crit = 0;

    critical[node] = (win_as_root[node] == 0);
    all_crit += par_crit;
    if (!par_win) lose_crit += par_crit;
    if ((win_as_root[node] == 1 && !par_win) || !win_as_root[node])
        critical[node] += par_crit;
    for (int i : graph[node]) if (i != parent) {
        all_crit += critical[i];
        if (!win_as_root[i]) lose_crit += critical[i];
        if ((win_as_root[node] == 1 && !win_as_root[i]) || !win_as_root[node])
            critical[node] += critical[i];
    }

    for (int i : graph[node]) if (i != parent) {
        if (win_as_root[node] - (win_as_root[i] == 0) == 0)
            dfs2(i, node, false, all_crit - critical[i] + 1);
        else if (win_as_root[node] - (win_as_root[i] == 0) == 1)
            dfs2(i, node, true, lose_crit - (win_as_root[i] ? 0 : critical[i]));
        else
            dfs2(i, node, true, 0);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, d;
    cin >> n >> d;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs1();
    dfs2();

    ll lose_cnt = 0, e_val = 0;
    for (int i = 1; i <= n; i++) {
        if (win_as_root[i]) e_val += critical[i];
        else lose_cnt++, e_val -= critical[i];
    }
    e_val = (e_val % MOD + MOD) % MOD;

    ll num = (expo(n, 2 * d) - expo(e_val, d) + MOD) % MOD;
    ll denom = expo((n * n - e_val + MOD) % MOD, MOD - 2);
    ll dp = lose_cnt * num % MOD * denom % MOD;
    if (win_as_root[1])
        cout << (expo(n, 2 * d) - critical[1] * dp % MOD + MOD) % MOD;
    else
        cout << critical[1] * dp % MOD;
    return 0;
}