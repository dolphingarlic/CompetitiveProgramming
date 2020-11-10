/*
IZhO 2017 Subsequence
- 20 = 10 + 10 and O(2^10 * N) is fast enough
- Let dp[f][l][b] = The longest subsequence so far that ends on some A[i] such that
    - The first 10 bits of A[i] are f
    - popcount(l & A[i]) == b
- If we know the longest subsequence that ends on some A[i], then we can update dp in O(2^10)
    - f is fixed, so just loop from 0 to 1023 (for values of l) and update the relevant values
- To find the longest subsequence that ends on some A[i]...
    - Loop f from 0 to 1023 and make sure that K[i] - 10 <= popcount(f & A[i]) <= K[i]
    - The answer for i is then the best dp[f][A[i] >> 10][K[i] - popcount(A[i] & j)]
- Complexity: O(2^10 * N)
*/

#include <bits/stdc++.h>
#define popcnt __builtin_popcount
using namespace std;

const int HM = 1 << 10, N = 1e5 + 1;

int a[N], k[N];
pair<int, int> dp[HM][HM][11], ans[N];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) {
		scanf("%d", k + i);
		pair<int, int> best = {0, 0};
		for (int j = 0; j < HM; j++)
			if (popcnt(a[i] & j) <= k[i] && k[i] - popcnt(a[i] & j) <= 10)
				best = max(best, dp[j][a[i] >> 10][k[i] - popcnt(a[i] & j)]);
		best.first++;
		ans[i] = best;
		for (int j = 0; j < HM; j++)
			dp[a[i] & HM - 1][j][popcnt((a[i] >> 10) & j)] = max(dp[a[i] & HM - 1][j][popcnt((a[i] >> 10) & j)], {best.first, i});
	}
	int idx = max_element(ans + 1, ans + n + 1) - ans;
	printf("%d\n", ans[idx].first);
	stack<int> seq;
	while (idx) {
		seq.push(idx);
		idx = ans[idx].second;
	}
	while (seq.size()) {
		printf("%d ", seq.top());
		seq.pop();
	}
	return 0;
}