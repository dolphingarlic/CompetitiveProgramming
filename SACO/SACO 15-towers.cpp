/*
SACO 2015 Towers
- Square root decomposition
- First, flatten the tree using an Euler tour
- Let indiv[tin[i]] = w[i] and indiv[tout[i]] = -w[i]
- Notice how sum(indiv[0]..indiv[y]) - sum(indiv[0]..indiv[x]) = Sum of weights on the path x->y
- Now, split the flattened tree up into sqrt(N) blocks
- In each block, store the sum of that block and a map of sum(indiv[block begin]..indiv[block begin + i])
- When we update some node, we simply change indiv at 2 positions and their respective blocks
    - This happens in O(sqrt(N)) time
- When we query some node, iterate over the blocks while maintaining a prefix sum. There are 3 cases:
    - Case 1: The current block is outside the range [tin[x], tout[x]]
        - Do nothing
        - O(1)
    - Case 2: The current block is inside the range but does not contain endpoints
        - Assuming that pref is sum(indiv[tin[x]]..indiv[current block start]),
          add cnt[current block][y - pref] to the answer
        - Then add the block sum to pref
        - O(1)
    - Case 3: The current block contains at least one of the endpoints
        - Iterate through all elements of this block and check whether it's in x's subtree and whether
          the sum of nodes from x to that node is equal to y
        - O(sqrt(N))
    - Notice how we encounter case 3 at most twice per query, so the queries are still O(sqrt(N))
- Complexity: O(N + Q sqrt(N))
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int N = 150000, B = 1000;

vector<int> graph[N];
ll w[N];
int tin[N], tout[N], timer = 0, b_timer = 0;
bool is_in[2 * N];

ll sm[2 * N / B], indiv[2 * N];
unordered_map<ll, int> cnt[2 * N / B];

void dfs(int node = 0) {
    sm[b_timer] += w[node];
    cnt[b_timer][sm[b_timer]]++;
    is_in[timer] = true;
    tin[node] = timer++;
    if (timer % B == 0) b_timer++;
    for (int i : graph[node]) dfs(i);
    sm[b_timer] -= w[node];
    tout[node] = timer++;
    if (timer % B == 0) b_timer++;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    FOR(i, 0, n) {
        int x;
        cin >> x;
        if (~x) graph[x].push_back(i);
    }
    FOR(i, 0, n) cin >> w[i];
    dfs();
    FOR(i, 0, n) indiv[tin[i]] = w[i], indiv[tout[i]] = -w[i];

    while (q--) {
        int t, x;
        ll y;
        cin >> t >> x >> y;
        int l = tin[x] / B, r = tout[x] / B;
        if (t) {
            indiv[tin[x]] = y;
            indiv[tout[x]] = -y;

            sm[l] = 0;
            cnt[l].clear();
            FOR(i, l * B, l * B + B) {
                sm[l] += indiv[i];
                if (is_in[i]) cnt[l][sm[l]]++;
            }
            sm[r] = 0;
            cnt[r].clear();
            FOR(i, r * B, r * B + B) {
                sm[r] += indiv[i];
                if (is_in[i]) cnt[r][sm[r]]++;
            }
        } else {
            int ans = 0;
            ll pref_sum = 0;
            FOR(i, 0, B) {
                if (i == l || i == r) {
                    FOR(j, i * B, min(timer, i * B + B)) {
                        if (j == tin[x]) pref_sum = 0;
                        pref_sum += indiv[j];
                        if (is_in[j] && j >= tin[x] && j <= tout[x] && pref_sum == y) ans++;
                    }
                } else {
                    if (i > l && i < r) ans += cnt[i][y - pref_sum];
                    pref_sum += sm[i];
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}