/*
Infoarena xortransform
- First, we can try brute force over 1*N boards
- Doing this lets us see that we have a Sierpinski-like pattern
- Also, the period is 2^ceil(log2(N))
- We can easily generalise this to the 2d case to see that the period is 2^max(ceil(log2(N)), ceil(log2(M)))
- From Sierpinski, we find that the problem becomes finding the xor sum of elements (i, j) in the
  matrix with the number of paths from (0, 0) to (i, j) after k transformations is odd
- The number of paths is equal to kCi * kCj (i.e. k choose i/j)
    - This means we must have both kCi and kCj odd
    - Also, by Lucas' theorem, if nCk is odd then n&k = k
- If nCi and nCj are odd, then we also have nC(i | j) is odd, so we can reduce this to SOS dp
- dp[i] = xor sum of elements that are included after i transformations
        -> dp[i - 1<<pos] ^ dp[i] if i & (1<<pos) == (1<<pos)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m, q, dp[2500001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    freopen("xortransform.in", "r", stdin);
    freopen("xortransform.out", "w", stdout);

    cin >> n >> m >> q;
    FOR(i, 0, n) FOR(j, 0, m) {
        int x;
        cin >> x;
        dp[i | j] ^= x;
    }

    int b2 = 1, cnt = 1;
    while (b2 < n || b2 < m) {
        b2 <<= 1;
        cnt++;
    }

    FOR(i, 0, cnt) FOR(j, 0, b2) {
        if (j & (1 << i)) dp[j] ^= dp[j ^ (1 << i)];
    }

    int prev = 0;
    while (q--) {
        int x;
        cin >> x;
        x ^= prev;
        x &= (b2 - 1);
        prev = dp[x];
        cout << prev << '\n';
    }
    return 0;
}