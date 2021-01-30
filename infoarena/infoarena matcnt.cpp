/*
Infoarena matcnt
- Firstly, the order of the rows doesn't matter because we can permute them, so just
  multiply the answer by N! at the end
- Consider a graph with N nodes and an edge between u and v if some row in our matrix
  has the 1s in columns u and v
- Each node in this graph has 2 edges going to 2 different nodes
- This means the graph is made up of several simple cycles of length >= 3
- To count how many of these graphs there are, let dp[i] be the answer for i nodes
    - dp[3] = 1
    - dp[i + 1] += dp[i] * i                  If we append node (i + 1) to some cycle
    - dp[i + 3] += dp[i] * (i + 2 choose 2)   If we create a new 3-cycle with node (i + 3)
- We can thus calculate dp[N] in linear time
- Complexity: O(N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 2e5 + 3;

ll dp[100004], fact = 6;

int main() {
    ifstream cin("matcnt.in");
    ofstream cout("matcnt.out");
    int n;
    cin >> n;
    dp[3] = 1;
    for (ll i = 3; i < n; i++) {
        dp[i + 1] = (dp[i + 1] + dp[i] * i) % MOD;
        dp[i + 3] = (dp[i + 3] + dp[i] * (i + 1) * (i + 2) / 2) % MOD;
        fact = fact * (i + 1) % MOD;
    }
    cout << dp[n] * fact % MOD;
    return 0;
}