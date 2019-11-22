#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int w[1000001], orig[1000001], nxt[1000001];
ll cnt;
bool visited[1000001];

pair<ll, ll> dfs(int node) {
    cnt++;
    visited[node] = true;
    if (!visited[nxt[node]]) {
        pair<ll, ll> res = dfs(nxt[node]);
        res.first += w[node];
        res.second = min(res.second, (ll)w[node]);
        return res;
    } else return {w[node], w[node]};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, mn = INT_MAX;
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> w[i];
        mn = min(mn, w[i]);
    }
    FOR(i, 1, n + 1) cin >> orig[i];
    FOR(i, 1, n + 1) {
        int x;
        cin >> x;
        nxt[x] = orig[i];
    }

    ll ans = 0;
    FOR(i, 1, n + 1) {
        if (!visited[i]) {
            cnt = 0;
            pair<ll, ll> res = dfs(i);
            ans += res.first + min((cnt - 2) * res.second, (cnt + 1) * mn + res.second);
        }
    }

    cout << ans;
    return 0;
}