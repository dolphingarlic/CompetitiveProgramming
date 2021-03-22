#include <bits/stdc++.h>
using namespace std;

int dp[2][10000], h[10000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> h[i];

    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (h[j] < h[i] && h[i] - h[j] <= q)
                dp[0][i] = max(dp[0][i], dp[0][j] + 1);

    for (int i = n - 2; ~i; i--)
        for (int j = n - 1; j > i; j--)
            if (h[j] < h[i] && h[i] - h[j] <= q)
                dp[1][i] = max(dp[1][i], dp[1][j] + 1);
    
    for (int i = 0; i < n; i++) cout << max(dp[0][i], dp[1][i]) + 1 << '\n';
    return 0;
}
