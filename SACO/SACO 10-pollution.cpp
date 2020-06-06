/*
SACO 2010 PPP
- If we probe position x and get pollution, we know the factory
  is in the range [x, N]
- Otherwise, it's in the range[1, x - 1]
- Let dp[i] = The minimum time it takes to find the factory if you
  know it's in the range [1, i] and you're at the mouth
    - Since this problem is symmetrical, this is the same as if you
      were at the source of the river
- dp[i] = min(max(dp[j], dp[i - j]) + j * t + s for all j < i)
- Complexity: O(N^2)
*/

#include <bits/stdc++.h>

int dp[10001], pos[10001];

int main() {
    int n, s, t;
    scanf("%d %d %d", &n, &s, &t);
    for (int i = 2; i <= n; i++) {
        dp[i] = INT_MAX;
        for (int j = 1; j < i; j++) {
            if (std::max(dp[j], dp[i - j]) + j * t + s < dp[i]) {
                dp[i] = std::max(dp[j], dp[i - j]) + j * t + s;
                pos[i] = j + 1;
            }
        }
    }
    printf("%d\n%d", dp[n], pos[n]);
    return 0;
}