/*
COI 2019 Ljetopica
- Imagine instead that we want to find the sum of end nodes that are only less than
  some X
    - Let this number be f(X)
    - Clearly, the answer to our original problem is f(B) - f(A - 1)
- dp[i][j][k][l] = Number of ways to end up at level i after making j changes such
                   that the current "left" is l and k denotes whether the final node
                   is guaranteed to be less than X
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll inv[1001], dp[1001][1001][2][2];

ll f(int n, int k, string instruct, string x) {
    if (x[0] == '0') return 0;
    dp[0][0][0][0] = dp[0][0][0][1] = 1;
    for (int i = 1; i < n; i++) for (int j = 0; j < k; j++) {
        memset(dp[i][j], 0, sizeof dp[i][j]);
        if (x[i] == '0') {
            
        } else {

        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    string instruct, a, b;
    cin >> n >> k >> instruct >> a >> b;
    inv[n] = 1;
    for (int i = n - 1; i; i--) inv[i] = (inv[i + 1] << 1) % MOD;
    for (int i = n - 1; ~i; i--) {
        if (a[i] == '1') {
            a[i] = '0';
            break;
        } else a[i] = '1';
    }
    cout << (f(n, k, instruct, b) - f(n, k, instruct, a) + MOD) % MOD;
    return 0;
}