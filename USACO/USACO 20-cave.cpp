#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll node[1001][1001];
set<ll> graph[1000001], to_process[1001];

bool visited[1000001];

ll cmp[1000001];
ll dp[1000001];
ll find(ll A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}
void onion(ll A, ll B) { cmp[find(A)] = cmp[find(B)]; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("cave.in", "r", stdin);
    freopen("cave.out", "w", stdout);
    ll n, m, cnt = 0;
    bool active = false;
    cin >> n >> m;
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            char c;
            cin >> c;
            if (c == '.') {
                if (!active) node[i][j] = ++cnt;
                else node[i][j] = cnt;
                active = true;
                if (node[i - 1][j]) graph[node[i - 1][j]].insert(cnt);
            } else {
                if (active) to_process[i].insert(cnt);
                active = false;
            }
        }
    }
    
    FOR(i, 1, cnt + 1) cmp[i] = i;

    for (ll i = n; i; i--) {
        for (ll j : to_process[i]) {
            dp[j] = 1;
            for (ll k : graph[j]) {
                if (j != find(k)) {
                    dp[j] = (dp[j] * dp[find(k)]) % MOD;
                    onion(k, j);
                }
            }
            assert(j == find(j));
        }
        for (ll j : to_process[i]) dp[j] = (dp[j] + 1) % MOD;
    }

    ll ans = 1;
    FOR(i, 1, cnt + 1) if (!visited[find(i)]) {
        visited[find(i)] = true;
        ans = (ans * dp[find(i)]) % MOD;
    }
    cout << ans;
    return 0;
}