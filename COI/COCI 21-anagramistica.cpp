/*
COCI 2021 Anagramistica
- Sort each word and accumulate a frequency table
- dp[i][j] = Ways to choose from the first i types of words
             and have j similar pairs
           = sum(dp[i - 1][j - (k choose 2)] * (cnt[i] choose k))
- Complexity: O(NK * sqrt(N))?
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll expo(ll base, ll pow) {
    ll ans = 1;
    while (pow) {
        if (pow & 1) ans = ans * base % MOD;
        pow >>= 1;
        base = base * base % MOD;
    }
    return ans;
}

ll fact[2001], chs[2001], dp[2001][2001];
map<string, int> mp;
int cnt[2001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    fact[0] = 1;
    for (int i = 1; i <= k; i++) fact[i] = fact[i - 1] * i % MOD;
    while (n--) {
        string s;
        cin >> s;
        sort(s.begin(), s.end());
        mp[s]++;
    }
    int m = 0;
    for (auto i : mp) cnt[++m] = i.second;
    dp[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        chs[0] = 1;
        for (int j = 1; j <= cnt[i]; j++)
            chs[j] = chs[j - 1] * (cnt[i] - j + 1) % MOD * expo(j, MOD - 2) % MOD;

        for (int j = 0; j <= k; j++) {
            for (int l = 0; l <= cnt[i]; l++) {
                if (l * (l - 1) / 2 > j) break;
                dp[i][j] += dp[i - 1][j - l * (l - 1) / 2] * chs[l] % MOD;
                if (dp[i][j] >= MOD) dp[i][j] -= MOD;
            }
        }
    }
    cout << dp[m][k];
    return 0;
}