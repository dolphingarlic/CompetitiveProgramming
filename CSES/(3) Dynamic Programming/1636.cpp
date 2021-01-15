#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 1000000007;
int dp[101][1010101], v[101];
 
int main() {
	int n, x;
	cin >> n >> x;
	for (int i = 1; i <= n; i++) cin >> v[i];
	sort(v + 1, v + n + 1);
	
	memset(dp, 0, sizeof(dp));
	
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < v[i]; j++) dp[i][j] = dp[i - 1][j];
		for (int j = v[i]; j <= x; j++) {
			dp[i][j] = (dp[i - 1][j] + dp[i][j - v[i]]) % MOD;
		}
	}
	
	cout << dp[n][x];
	return 0;
}