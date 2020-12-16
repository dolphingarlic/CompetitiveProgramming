/*
Balkan 2009 Reading
- dp[i][j] = The number of ways to get a word ending on i with complexity j
           = sum(dp[k][j - complexity(k->i)])
- This is a linear recurrence, so we can calculate it using matrix exponentiation
- To sum all dp values, add an additional row to "collect" the values
- Complexity: O((26 * 5)^3 log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;
const int MAX_DIST = 5;

vector<vector<ll>> matmult(vector<vector<ll>> a, vector<vector<ll>> b) {
	assert(a[0].size() == b.size());
	vector<vector<ll>> c(a.size(), vector<ll>(b[0].size(), 0));
	for (int i = 0; i < a.size(); i++) for (int j = 0; j < b[0].size(); j++) {
		for (int k = 0; k < b.size(); k++) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
	}
	return c;
}

vector<vector<ll>> expo(vector<vector<ll>> a, ll pow) {
	assert(a.size() == a[0].size());
	vector<vector<ll>> ans(a.size(), vector<ll>(a.size(), 0));
	for (int i = 0; i < a.size(); i++) ans[i][i] = 1;
	while (pow) {
		if (pow & 1) ans = matmult(ans, a);
		a = matmult(a, a);
		pow >>= 1;
	}
	return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<vector<ll>> mat(26 * 5 + 1, vector<ll>(26 * 5 + 1, 0));
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) mat[5 * i][5 * j] = 1;
        for (int j = 0; j < 4; j++) mat[5 * i + j + 1][5 * i + j] = 1;
    }
    for (int i = 0; i < 26; i++) mat[5 * 26][5 * i] = 1;
    mat[5 * 26][5 * 26] = 1;

    ll n;
    int m;
    cin >> n >> m;
    while (m--) {
        char a, b;
        int f;
        cin >> a >> b >> f;
        int x = 5 * (a - 'a'), y = 5 * (b - 'a');
        mat[x][y] = mat[y][x] = 0;
        mat[x][y + f - 1] = mat[y][x + f - 1] = 1;
    }
    vector<vector<ll>> res = expo(mat, n + 1);
    ll ans = 0;
    for (int i = 0; i < 26; i++) ans = (ans + res[5 * 26][5 * i]) % MOD;
    cout << ans;
    return 0;
}