#include <cstdio>

const int MOD = 1e8;

int dp[2][1000];
char c[1000];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", c);
        for (int j = 0; j < m; j++) {
            dp[i & 1][j] = (!i && !j);
            if (c[j] == '.') {
                dp[i & 1][j] += dp[i - 1 & 1][j];
                if (j) dp[i & 1][j] += dp[i & 1][j - 1];
            } else dp[i & 1][j] = 0;
            if (dp[i & 1][j] >= MOD) dp[i & 1][j] -= MOD;
        }
    }
    printf("%d", dp[n - 1 & 1][m - 1]);
    return 0;
}