/*
CEOI 2016 Kangaroo
- We basically want the number of permutations where the first and last elements are A and B respectively
  and the condition of jumping back and forth holds
- dp[i][j] = The number of ways to insert 1..i into the permutation such that there are j connected components
- dp[0][0] = 1
- If i == a or i == b, then dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] (since they have to go to the ends)
- Otherwise, dp[i][j] = dp[i - 1][j + 1] * j + dp[i - 1][j - 1] * (j - (i > a) - (i > b))
- Complexity: O(N^2)
*/

#include <cstdio>
using namespace std;

const long long MOD = 1e9 + 7;

long long dp[2001][2001];

int main() {
	int n, a, b;
	scanf("%d %d %d", &n, &a, &b);
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
		if (i == a || i == b)
			dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
		else
			dp[i][j] = (dp[i - 1][j + 1] * j + dp[i - 1][j - 1] * (j - (i > a) - (i > b))) % MOD;
	}
	printf("%lld\n", dp[n][1]);
	return 0;
}