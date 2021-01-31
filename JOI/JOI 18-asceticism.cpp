/*
JOI 2018 Asceticism
- dp[i][j] = Number of permutations of length i with j indices x such that p[x] > p[x + 1]
           = j * dp[i - 1][j] + (i - j + 1) * dp[i - 1][j - 1]
           = A(i, j) i.e. an Eulerian number
- There's an explicit formula for Eulerian numbers
    - A(i, j) = sum((i - K)^N * (N + 1 choose i) for each i from 0 to K)
    - Reference: https://en.wikipedia.org/wiki/Eulerian_number#Explicit_formula
    - Proof: https://www.quora.com/Is-there-a-combinatorial-proof-of-the-closed-form-for-Eulerian-numbers
- Complexity: O(N log N) because of modular inverses
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll expo(ll base, ll pow) {
    ll ans = 1;
    while (pow) {
        if (pow & 1) ans = (ans * base) % MOD;
        base = (base * base) % MOD;
        pow >>= 1;
    }
    return ans;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    ll ans = 0, choose = 1, neg = 1;
    for (int i = 0; i <= k; i++) {
        ans = (ans + neg * choose % MOD * expo(k - i, n)) % MOD;
        choose = choose * (n + 1 - i) % MOD * expo(i + 1, MOD - 2) % MOD;
        neg = MOD - neg;
    }
    printf("%lld", ans);
    return 0;
}