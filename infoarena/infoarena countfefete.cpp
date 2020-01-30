/*
infoarena countfefete
- Simplified statement:
    You're given a tree with weighted edges. Define f(S) for some subset of the nodes as follows:
        First, take the xor sum of the weights of the nodes in S. Let this result be X
        Next, take the node with least weight on the shortest path between the nodes in S. Let the weight be Y
        f(S) = X ^ Y
    E.g. if we have 1 -- 2 -- 3, then f({1, 3}) = v[1] ^ v[3] ^ v[k] where v[k] = min(v[1], v[2], v[3])
    Find the sum of f(S) for all subsets of the nodes, modulo 1e9+7 

- Since xor for general integers is inconvenient, let's rather solve the problem a single bit at a time
    - This works since the set {0, 1} is closed under xor, so if we have the sum of subsets for a particular bit i
      (let's say this result is x), then we can simply add x<<i to the answer
- Sort the nodes in descending order by value. Now when we iterate through them, we may simply use DSU to find the
  component where the current node is the minimum one
- Notice how we only care about the total size of the component and the number of 1s in the component
    - Since we want to find the number of subsets in that component such that the xor sum is 1
    - E.g. If the current node has the current bit, then we want to choose an even number of other nodes
    - There are 2^(k-1) ways to choose a non-empty subset of odd size from k distict elements and there are
      2^(k-1) - 1 ways to choose a non-empty subset of even size from k distinct elements
- So we can use the principle of inclusion-exclusion to count the total number for each node and each bit and then add that to the answer
- Complexity: O(N log MAX_V)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

pair<ll, int> by_value[200001];
vector<int> graph[200001];
int cmp[200001];
ll val[200001], ones[200001][30], sz[200001], pw[200001];
ll dp[30], exclude[30];

void init(int n) {
    FOR(i, 1, n + 1) {
        cmp[i] = i;
        sz[i] = 1;
        FOR(j, 0, 30) {
            if (val[i] & (1 << j)) ones[i][j]++;
        }
    }

    sort(by_value + 1, by_value + n + 1);

    pw[0] = 1;
    FOR(i, 1, n + 1) {
        pw[i] = pw[i - 1] << 1;
        if (pw[i] >= MOD) pw[i] -= MOD;
    }
}

int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}

void onion(int A, int B) {
    FOR(i, 0, 30) {
        ones[find(B)][i] += ones[find(A)][i];
    }
    sz[find(B)] += sz[find(A)];
    cmp[find(A)] = find(B);
}

ll count_ways(int tot, int o, bool has) {
    if (has) {
        // Choose an even number of nodes
        ll ans = 0;
        ans = ((o ? pw[o - 1] - 1 : 0) * pw[tot - o]) % MOD;
        ans = (ans + pw[tot - o] - 1) % MOD;
        return ans;
    }
    // Else choose an odd number
    if (o == 0) return 0;
    return pw[tot - 1];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("countfefete.in", "r", stdin);
    freopen("countfefete.out", "w", stdout);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> val[i];
        by_value[i] = {-val[i], i};
    }
    FOR(i, 1, n) {
        int a, b;
        cin >> a >> b;
        if (val[a] < val[b]) graph[a].push_back(b);
        else graph[b].push_back(a);
    }
    init(n);

    ll ans = 0;
    FOR(i, 1, n + 1) {
        int node = by_value[i].second;
        FOR(j, 0, 30) {
            ll ways = 0, node_tot = sz[node], node_ones = ones[node][j];
            bool has = (val[node] & (1 << j));

            for (int k : graph[node]) {
                ways = (ways - count_ways(sz[find(k)], ones[find(k)][j], has) + MOD) % MOD;
                node_tot += sz[find(k)];
                node_ones += ones[find(k)][j];
            }
            ways = (ways + count_ways(node_tot, node_ones, has)) % MOD;
            ans = (ans + ways * (1 << j)) % MOD;
        }
        for (int j : graph[node]) onion(j, node);
    }

    cout << ans;
    return 0;
}