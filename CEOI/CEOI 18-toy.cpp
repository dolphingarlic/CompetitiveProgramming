/*
CEOI 2018 Toys
- dp[i] = Set of possible stuff for the i-th divisor of N
- Notice how dp[i] depends on dp[j] iff divisor[i] % divisor[j] == 0
- So just do it
- Complexity: O(???)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> divisors;
unordered_set<int> dp[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i * i <= n; i++) if (!(n % i)) {
        divisors.push_back(i);
        if (i * i != n) divisors.push_back(n / i);
    }
    sort(divisors.begin(), divisors.end());

    dp[0].insert(0);
    int d = divisors.size();
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < i; j++) {
            if (divisors[i] % divisors[j]) continue;
            for (int k : dp[j]) dp[i].insert(k + divisors[i] / divisors[j] - 1);
        }
    }

    set<int> res;
    for (int i : dp[d - 1]) res.insert(i);
    cout << res.size() << '\n';
    for (int i : res) cout << i << ' ';
    return 0;
}