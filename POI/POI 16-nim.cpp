/*
POI 2016 Nim
- dp[i][j][mask] = Ways to take away j piles from the first i piles
                   so that the xor of piles taken is mask
                 = dp[i - 1][j][mask] + dp[i - 1][j - 1][mask ^ a[i]]
- This lets us calculate dp in O(N^2 * MAX_A)
- The answer is sum(dp[N][D * i][xor of all a[i]]) - (N % D == 0)
- Observation 1: D is small
    - This means we can just make j -> j % D
    - Still O(N^2 * MAX_A), but we use less memory
- Observation 2: dp[i][j] depends only on dp[i - 1][j] and dp[i - 1][j - 1]
    - This means we don't have to iterate over each j less than i,
      but instead just those less than d
    - Also, we can drop i entirely to save more memory
        - Since the dependencies are kinda "circular", we need an auxilliary
          array to store one of the dp[j]'s
    - This drops the time complexity to O(N * D * MAX_A) and the memory down
      to O(D * MAX_A)
- Right now, we have:
    - dp[j % D][mask] := dp[j % D][mask] + dp[(j + D - 1) % D][mask ^ a[i]]
    - The answer is dp[N % 2][0][xor of all a[i]] - (N % D == 0)
- Observation 3: The sum of a[i] is small and order doesn't matter
    - This means we can sort the a[i] and process then in increasing order
    - Additionally, we only need to consider masks less than 2^ceil(log2(a[i]))
      for each i, since masks greater than that have dp = 0
    - This drops the time complexity down to amortized O(sum(a[i]) * D)
- Complexity: O(sum(a[i]) * D)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int MOD = 1e9 + 7;

int a[500001], dp[10][1 << 20], tmp[1 << 20];

void add(int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, d, xor_all = 0;
    cin >> n >> d;
    FOR(i, 1, n + 1) {
        cin >> a[i];
        xor_all ^= a[i];
    }
    sort(a + 1, a + n + 1);

    dp[0][0] = 1;
    int curr_mx = 1;
    FOR(i, 1, n + 1) {
        while (curr_mx <= a[i]) curr_mx <<= 1;
        memcpy(tmp, dp[d - 1], sizeof(int) * curr_mx);
        for (int j = d - 1; j; j--)
            FOR(k, 0, curr_mx) add(dp[j][k], dp[j - 1][k ^ a[i]]);
        FOR(k, 0, curr_mx) add(dp[0][k], tmp[k ^ a[i]]);
    }

    cout << (dp[0][xor_all] - (n % d == 0) + MOD) % MOD;
    return 0;
}