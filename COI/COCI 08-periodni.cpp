/*
COCI 2008 Periodni
- Notice how if we move from the y row upward, we get "islands" forming
    - Each island is independent and is also a smaller periodic table
    - This suggests that since the periodic table has no "donuts", we should
      compress it into a rooted tree
        - Kinda like IOI 2012 Ideal City
- The root node of a periodic table is the largest rectangle we can make from
  the y few rows
    - We can then recursively generate the rest of the tree
- dp[i][j] = The number of ways to put j noble gases in node i's subtree
- tmp[i][j] = dp[i][j] but we put no noble gases in node i
- dp[i][j] = sum(tmp[i][k] * choose(width[i] - k, j) * choose(height[i], j) * j!)
- Complexity: O(N^2 * K)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

int n, m = 0, k, h[500];
ll fact[1000001]{1}, inv_fact[1000001]{1};
ll width[500], height[500], dp[500][501], tmp[501];
vector<int> graph[500];

ll expo(ll base, ll pow) {
    ll ans = 1;
    while (pow) {
        if (pow & 1) ans = ans * base % MOD;
        pow >>= 1;
        base = base * base % MOD;
    }
    return ans;
}

ll choose(ll x, ll y) {
    if (x < y) return 0;
    return fact[x] * inv_fact[y] % MOD * inv_fact[x - y] % MOD;
}

void construct_tree(int l = 0, int r = n - 1, int dh = 0) {
    int min_h = *min_element(h + l, h + r + 1);
    width[m] = r - l + 1;
    height[m] = min_h - dh;

    int curr_idx = m++, curr_l = l;
    FOR(i, l, r + 1) {
        if (h[i] == min_h) {
            if (curr_l != i) {
                graph[curr_idx].push_back(m);
                construct_tree(curr_l, i - 1, min_h);
            }
            curr_l = i + 1;
        }
    }
    if (curr_l != r + 1) {
        graph[curr_idx].push_back(m);
        construct_tree(curr_l, r, min_h);
    }
}

void dfs(int node = 0) {
    dp[node][0] = 1;
    for (int i : graph[node]) {
        dfs(i);
        memset(tmp, 0, sizeof tmp);
        FOR(j, 0, width[node] + 1) {
            FOR(k, 0, width[i] + 1) {
                if (j + k > width[node]) continue;
                (tmp[j + k] += dp[node][j] * dp[i][k]) %= MOD;
            }
        }
        FOR(j, 0, width[node] + 1) dp[node][j] = tmp[j];
    }

    memset(tmp, 0, sizeof tmp);
    FOR(i, 0, width[node] + 1) {
        FOR(j, 0, width[node] + 1) {
            if (i + j > width[node]) continue;
            ll x = dp[node][i];
            ll y = choose(width[node] - i, j) * choose(height[node], j) % MOD * fact[j] % MOD;
            (tmp[i + j] += x * y) %= MOD;
        }
    }
    FOR(i, 0, width[node] + 1) dp[node][i] = tmp[i];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    FOR(i, 1, 1000001) {
        fact[i] = fact[i - 1] * i % MOD;
        inv_fact[i] = expo(fact[i], MOD - 2);
    }

    cin >> n >> k;
    FOR(i, 0, n) cin >> h[i];
    construct_tree();
    dfs();
    cout << dp[0][k];
    return 0;
}