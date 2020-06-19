/*
Baltic 2011 Meetings
- Let dp[i] = Answer if there are i people
- Notice how dp is non-decreasing
- This means if we have k groups of people, the answer
  depends on the largest group
- This gives us dp[i] = min(dp[ceil(i / j)] + dp[j])
- Notice how this is symmetrical, so we can just check j up to sqrt(i)
- If we expand this further, we get
  dp[i] = min(sum(dp[x_j])) where prod(x_j) >= i and dp[x_j] = x_j * P + V
        = sum(dp[x_j]) * P + k * V if there are k groups
- Since there's no point splitting groups of < 2 into subgroups, notice
  that we only need to check k for k <= log_2(N)
- Additionally, it's optimal to split the people into similarly sized groups
- This means we can check each k in O(k) time
- Complexity: O(log^2 N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll dp[50001];

ll solve_k(ll n, int p, int v, int k) {
    ll fact = ll(pow(n, 1.0 / k));
    int incr = 0;
    while (pow(fact + 1, incr) * pow(fact, k - incr) < n)
        incr++;
    return (k * fact + incr) * p + k * v;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    int p, v;
    cin >> n >> p >> v;
    
    if (n == 1) return cout << 0, 0;
    ll ans = LLONG_MAX;
    for (int i = 1; (1ll << i) <= n; i++)
        ans = min(ans, solve_k(n, p, v, i));
    cout << ans;
    return 0;
}