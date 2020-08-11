/*
Baltic 2017 Toll
- View the graph as a kind of neural network, where each layer has K nodes
- dp[i][j][x][y] = Minimum distance from node Ki + x to K(i + (1 << j)) + y
- Notice how we can combine dp[i][j] and dp[i + (1 << j)][j] to get dp[i][j + 1]
  in O(K^3) time (like Floyd-Warshall)
- This means we can do binary jumping to find the answer to each query
- Complexity: O(OK^3 log N/K)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int k, n, m, o;
int dp[50000][17][5][5], ans[5][5], tmp[5][5];

void combine(int target[5][5], int a[5][5], int b[5][5]) {
    for (int x = 0; x < k; x++) {
        for (int y = 0; y < k; y++) {
            for (int z = 0; z < k; z++) {
                target[x][y] = min(target[x][y], a[x][z] + b[z][y]);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> k >> n >> m >> o;
    memset(dp, 0x3f, sizeof dp);
    while (m--) {
        int a, b, t;
        cin >> a >> b >> t;
        dp[a / k][0][a % k][b % k] = t;
    }
    for (int j = 1; j < 17; j++) {
        for (int i = 0; i + (1 << j) < (n + k - 1) / k; i++) {
            combine(dp[i][j], dp[i][j - 1], dp[i + (1 << j - 1)][j - 1]);
        }
    }

    while (o--) {
        int a, b;
        cin >> a >> b;
        memset(ans, 0x3f, sizeof ans);
        for (int i = 0; i < 5; i++) ans[i][i] = 0;
        for (int curr = a / k, dest = b / k, i = 16; ~i; i--) {
            if (curr + (1 << i) <= dest) {
                memset(tmp, 0x3f, sizeof tmp);
                combine(tmp, ans, dp[curr][i]);
                memcpy(ans, tmp, sizeof ans);
                curr += (1 << i);
            }
        }
        cout << (ans[a % k][b % k] == 1061109567 ? -1 : ans[a % k][b % k]) << '\n';
    }
    return 0;
}